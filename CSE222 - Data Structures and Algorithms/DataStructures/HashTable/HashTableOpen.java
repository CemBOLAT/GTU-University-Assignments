

public class HashTableOpen <K, V>{
	private Entry<K, V>[] table;
	private int cap;
	private static final int DEFAULT_CAPACITY = 16;
	private static final float DEFAULT_LOAD_FACTOR = 0.75f;
	private int size;
	private int deletednums;

	private Entry<K, V> deleted = new Entry<K, V>(null, null); // tombstone

	public HashTableOpen(){
		table = new Entry[DEFAULT_CAPACITY];
		cap = DEFAULT_CAPACITY;
		size = 0;
		deletednums = 0;
	}

	private int getHashedIndex(Object key){
		int index = key.hashCode() % cap;
		if (index < 0){
			index += cap;
		}
		return index;
	}

	public V put(K key, V value){ // return the old value
		int index = getHashedIndex(key);
		while (table[index] != null && !table[index].getKey().equals(key)){
			index = (index + 1) % cap;
		}
		if(table[index] == null){
			table[index] = new Entry<K, V>(key, value);
			size++;
			if(size + deletednums >= cap * DEFAULT_LOAD_FACTOR){
				reHash();
			}
			return null;
		}
		else{
			V oldValue = table[index].getValue();
			table[index].setValue(value);
			return oldValue;
		}
	}

	public V remove(Object key){ // return the value
		int index = getHashedIndex(key);
		while (table[index] != null && !table[index].getKey().equals(key)){
			index = (index + 1) % cap;
		}
		if(table[index] == null){
			return null;
		}
		else{
			V oldValue = table[index].getValue();
			table[index] = deleted;
			deletednums++;
			size--;
			return oldValue;
		}

	}

	private void reHash(){
		Entry<K, V>[] oldTable = table;
		cap = cap * 2;
		table = new Entry[cap];
		size = 0;
		deletednums = 0;
		for(int i = 0; i < oldTable.length; i++){
			if(oldTable[i] != null && oldTable[i] != deleted){
				put(oldTable[i].getKey(), oldTable[i].getValue());
			}
		}
	}

	private int find(Object key){
		int index = getHashedIndex(key);
		while (table[index] != null && !table[index].getKey().equals(key)){
			index = (index + 1) % cap;
		}
		if(table[index] == null){
			return -1;
		}
		else{
			return index;
		}
	}

	public boolean isEmpty(){
		return size == 0;
	}

	public int size(){
		return size;
	}

	private static class Entry<K, V> {
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

		public void setValue(V value){
			this.value = value;
		}

		public boolean equals(Object obj){
			if(obj == this){
				return true;
			}
			if(obj instanceof Entry){
				Entry<K, V> entry = (Entry<K, V>) obj;
				return key.equals(entry.getKey()) && value.equals(entry.getValue());
			}
			return false;
		}

		public String toString(){
			return key + "=" + value;
		}
	}

}
