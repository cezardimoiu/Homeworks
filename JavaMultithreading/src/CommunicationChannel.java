/**
 * Class that implements the channel used by headquarters and space explorers to communicate.
 */

import java.util.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.atomic.AtomicInteger;

public class CommunicationChannel {
	/**
	 * Creates a {@code CommunicationChannel} object.
	 */
	private int parentSolarSystem;
	private int currentSolarSystem;
	private String data;

	private static String NO_PARENT = "NO_PARENT";
	private static String END = "END";
	public static String EXIT = "EXIT";

	Map<Thread, LinkedList<Message>> map = Collections.synchronizedMap(new HashMap<Thread, LinkedList<Message>>());

	LinkedList<Message> toSend = new LinkedList<>();
	ArrayList<Message> aux_list_to_send = new ArrayList<>();

	public CommunicationChannel() {
	}

	public void setCurrentSolarSystem(int currentSolarSystem) {
		this.currentSolarSystem = currentSolarSystem;
	}

	public int getCurrentSolarSystem() {
		return currentSolarSystem;
	}

	public void setParentSolarSystem(int parentSolarSystem) {
		this.parentSolarSystem = parentSolarSystem;
	}

	public int getParentSolarSystem() {
		return parentSolarSystem;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}
	/**
	 * Puts a message on the space explorer channel (i.e., where space explorers write to and
	 * headquarters read from).
	 *
	 * @param message
	 *            message to be put on the channel
	 */

	public void putMessageSpaceExplorerChannel(Message message) {
		synchronized (toSend) {
			toSend.addLast(message);
		}
	}

	/**
	 * Gets a message from the space explorer channel (i.e., where space explorers write to and
	 * headquarters read from).
	 * 
	 * @return message from the space explorer channel
	 */
	public Message getMessageSpaceExplorerChannel() {
		synchronized (toSend) {
			if (toSend.isEmpty())
				return null;
			else {
				return toSend.removeFirst();
			}
		}
	}

	/**
	 * Puts a message on the headquarters channel (i.e., where headquarters write to and
	 * space explorers read from).
	 * 
	 * @param message
	 *            message to be put on the channel
	 */
	public void putMessageHeadQuarterChannel(Message message) {

		synchronized (map) {
			Thread currThread = Thread.currentThread();
			if (message.getData().equals(END) || message.getData().equals(EXIT)) {

			}
			else if (map.get(currThread) == null || map.get(currThread).isEmpty()) {
				//nu e niciun element sau cand am in lista ele
				setParentSolarSystem(message.getCurrentSolarSystem());
				// pun mesaj cu (root, -1, null);
				Message msg = new Message(parentSolarSystem, -1, null);
				if (map.get(currThread) == null)
					map.put(currThread, new LinkedList<Message>());
				map.get(currThread).addFirst(msg);
				//lista are un element incomplet
			} else {
				setCurrentSolarSystem(message.getCurrentSolarSystem());
				setData(message.getData());
				if (!map.get(currThread).isEmpty()) {
					Message msg = map.get(currThread).getFirst();
					msg.setCurrentSolarSystem(currentSolarSystem);
					msg.setData(data);
					//ma asigur ca elementul e complet, il trimit la space_explorer
					synchronized (aux_list_to_send) {
						aux_list_to_send.add(msg);
					}
					map.get(currThread).removeFirst();
				}
			}
		}
	}

	/**
	 * Gets a message from the headquarters channel (i.e., where headquarters write to and
	 * space explorer read from).
	 * 
	 * @return message from the header quarter channel
	 */
	public Message getMessageHeadQuarterChannel() {
		synchronized (aux_list_to_send) {
			if (aux_list_to_send.isEmpty())
				return new Message(-1, "WRong");
			else {
				int size = aux_list_to_send.size();
				Message x = aux_list_to_send.get(size - 1);
				aux_list_to_send.remove(size - 1);
				return x;
			}
		}
	}
}
