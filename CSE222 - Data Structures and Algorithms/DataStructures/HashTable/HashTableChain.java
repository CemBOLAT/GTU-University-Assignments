import java.util.LinkedList;

public class HashTableChain <K,V> {
	private LinkedList<Entry<K,V>>[] table;
	private int size;
	private int cap;
	private static final int DEFAULT_CAPACITY = 16;
	private static final double DEFAULT_LOAD_FACTOR = 0.75;

	public HashTableChain(){
		table = new LinkedList[DEFAULT_CAPACITY];
		cap = DEFAULT_CAPACITY;
		size = 0;
	}

	private int getHashedIndex(Object key){
		int index = key.hashCode() % cap;
		if(index < 0){
			index += cap;
		}
		return index;
	}

	public V put(K key, V value){
		int index = getHashedIndex(key);
		if(table[index] == null){
			table[index] = new LinkedList<>();
			size++;
		} else {
			for (var entry : table[index]){
				if(entry.getKey().equals(key)){
					V oldValue = entry.getValue();
					entry.setValue(value);
					return oldValue;
				}
			}
		}
		table[index].add(new Entry<K,V>(key, value));
		// size++; is may be wrong here
		if (size >= cap * DEFAULT_LOAD_FACTOR){
			reHash();
		}
		return null;
	}

	public V remove(Object key){
		int index = getHashedIndex((Object)key); // imcompatible types K and Object fix this
		if(table[index] == null){
			return null;
		}
		for (var entry : table[index]){
			if(entry.getKey().equals(key)){
				V oldValue = entry.getValue();
				table[index].remove(entry);
				size--;
				return oldValue;
			}
		}
		return null;
	}

	public V get(Object key){
		int index = getHashedIndex(key);

		if(table[index] == null){
			return null;
		}

		for (var entry : table[index]){
			if(entry.getKey().equals(key)){
				return entry.getValue();
			}
		}

		return null;
	}

	private void reHash(){
		LinkedList<Entry<K,V>>[] oldTable = table;
		cap = cap * 2;
		table = new LinkedList[cap];
		size = 0;
		for (var list : oldTable){
			if(list != null){
				for (var entry : list){
					put(entry.getKey(), entry.getValue());
				}
			}
		}
	}

	private static class Entry<K,V>{
		K key;
		V value;
		public Entry(K key, V value){
			this.key = key;
			this.value = value;
		}
		public K getKey(){
			return key;
		}
		public V getValue(){
			return value;
		}
		public V setValue(V value){
			V oldValue = this.value;
			this.value = value;
			return oldValue;
		}
	}

}
