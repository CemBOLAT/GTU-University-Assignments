import java.util.Iterator;

public class DoubleLinkedList<E> implements Iterable<E> {
	private Node<E> head;
	private Node<E> tail;
	private int size;

	public DoubleLinkedList() {
		size = 0;
		head = null;
		tail = null;
	}

	public boolean isEmpty() {
		return size == 0;
	}

	public boolean contains(E element) {
		Node<E> tmp = head;
		while (tmp != null) {
			if (element.equals(tmp.data))
				return true;
			tmp = tmp.next;
		}
		return false;
	}

	public int indexOf(E element) {
		Node<E> tmp = head;
		int index = 0;
		while (tmp != null) {
			if (element.equals(tmp.data))
				return index;
			tmp = tmp.next;
			index++;
		}
		return -1;
	}

	public void addFirst(E element) {
		Node<E> newNode = new Node<>(element);
		if (isEmpty()) {
			head = newNode;
			tail = newNode;
		} else {
			newNode.next = head;
			head.prev = newNode;
			head = newNode;
		}
		size++;
	}

	public void addLast(E element) {
		Node<E> newNode = new Node<>(element);
		if (isEmpty()) {
			head = newNode;
			tail = newNode;
		} else {
			tail.next = newNode;
			newNode.prev = tail;
			tail = newNode;
		}
		size++;
	}

	public void add(E element) {
		addLast(element);
	}

	public void add(int index, E element) {
		if (index < 0 || index > size)
			throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
		if (index == 0) {
			addFirst(element);
		} else if (index == size) {
			addLast(element);
		} else {
			Node<E> newNode = new Node<>(element);
			Node<E> tmp = head;
			for (int i = 0; i < index - 1; i++) {
				tmp = tmp.next;
			}
			newNode.next = tmp.next;
			tmp.next.prev = newNode;
			tmp.next = newNode;
			newNode.prev = tmp;
			size++;
		}
	}

	public E removeFirst() {
		if (isEmpty())
			throw new IndexOutOfBoundsException("Empty list");
		E data = head.data;
		head = head.next;
		if (head != null)
			head.prev = null;
		size--;
		return data;
	}

	public E removeLast() {
		if (isEmpty())
			throw new IndexOutOfBoundsException("Empty list");
		E data = tail.data;
		tail = tail.prev;
		if (tail != null)
			tail.next = null;
		size--;
		return data;
	}

	public E remove(int index) {
		if (index < 0 || index >= size)
			throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
		if (index == 0) {
			return removeFirst();
		} else if (index == size - 1) {
			return removeLast();
		} else {
			Node<E> tmp = head;
			for (int i = 0; i < index - 1; i++) {
				tmp = tmp.next;
			}
			E data = tmp.next.data;
			tmp.prev.next = tmp.next;
			tmp.next.prev = tmp.prev;
			size--;
			return data;
		}
	}

	public E getFirst() {
		if (isEmpty())
			throw new IndexOutOfBoundsException("Empty list");
		return head.data;
	}

	public E getLast() {
		if (isEmpty())
			throw new IndexOutOfBoundsException("Empty list");
		return tail.data;
	}

	public E get(int index) {
		if (index < 0 || index >= size)
			throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
		Node<E> tmp = head;
		for (int i = 0; i < index; i++) {
			tmp = tmp.next;
		}
		return tmp.data;
	}

	public void set(int index, E element) {
		if (index < 0 || index >= size)
			throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
		Node<E> tmp = head;
		for (int i = 0; i < index; i++) {
			tmp = tmp.next;
		}
		tmp.data = element;
	}

	public int size() {
		return size;
	}

	public void clear() {
		head = null;
		tail = null;
		size = 0;
    }

    public Iterator<E> iterator() {
        return new ListIterator();
    }

    private class Node<E> {
        E data;
        Node<E> prev;
        Node<E> next;

        public Node(E data) {
            this.data = data;
            this.prev = null;
            this.next = null;
        }
    }

    public class ListIterator implements Iterator<E> {
        private Node<E> current;

        public ListIterator() {
            current = head;
        }

        public boolean hasNext() {
            return current != null;
        }

        public boolean hasPrevious() {
            return current != null && current.prev != null;
        }

        public E next() {
            E data = current.data;
            current = current.next;
            return data;
        }

        public E previous() {
            E data = current.data;
            current = current.prev;
            return data;
        }

        public void remove() {
            if (current == head) {
                removeFirst();
            } else if (current == tail) {
                removeLast();
            } else {
                current.prev.next = current.next;
                current.next.prev = current.prev;
                size--;
            }
        }

        public void set(E element) {
            current.data = element;
        }
    }

}
