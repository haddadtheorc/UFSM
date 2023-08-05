package ibd.transaction.concurrency.locktable.items;

import java.util.ArrayList;

import ibd.transaction.concurrency.Item;

public class HaddadItemCollection implements ItemCollection {
    static class Node {
        Item item;
        long max;
        Node left, right;

        public Node(Item item) {
            this.item = item;
            this.max = item.getHigher();
        }
    }

    Node items;

    private Node insertNode(Node root, Item item) {
        Node n = new Node(item);

        if (root == null) return n;

        long i = root.item.getLower();

        if (i > item.getLower()) {
            root.left = insertNode(root.left, item);
        } else {
            root.right = insertNode(root.right, item);
        }

        if (root.max < item.getHigher()) {
            root.max = item.getHigher();
        }

        return root;
    }

    private Node searchNode(Node root, long lower, long higher) {
        if (root == null) return null;

        if (root.item.getLower() == lower && root.item.getHigher() == higher) {
            return root;
        } else {
            if (root.item.getLower() > lower) {
                return searchNode(root.left, lower, higher);
            } else {
                return searchNode(root.right, lower, higher);
            }
        }
    }

    private void searchAllNodes(Node root, ArrayList<Item> list) {
        if (root == null) return;

        list.add(root.item);
        searchAllNodes(root.left, list);
        searchAllNodes(root.right, list);
    }

    private void searchOverlapNodes(Node root, Item item, ArrayList<Item> list) {
        if (root == null) return;

        if (root.item.getLower() <= item.getHigher() && root.item.getHigher() >= item.getLower()) {
            list.add(root.item);
            searchOverlapNodes(root.left, item, list);
            searchOverlapNodes(root.right, item, list);
        } else if (root.left != null && root.left.max > item.getLower()) {
            searchOverlapNodes(root.left, item, list);
        } else if (root.right != null && root.right.item.getLower() < item.getHigher()) {
            searchOverlapNodes(root.right, item, list);
        }
    }

    @Override
    public Item addItem(long lower, long higher) {
        Item item = getItem(lower, higher);

        if (item == null) {
            item = new Item(lower, higher);
            items = insertNode(items, item);
        }
        return item;
    }

    @Override
    public Item getItem(long lower, long higher) {
        Node n = searchNode(items, lower, higher);

        if (n == null) return null;

        return n.item;
    }

    @Override
    public Iterable<Item> getAllItems() {
        ArrayList<Item> i = new ArrayList<>();

        searchAllNodes(items, i);

        return i;
    }

    @Override
    public Iterable<Item> getOverlappedItems(long lower, long higher) {
        ArrayList<Item> list = new ArrayList<>();
        Item item = new Item(lower, higher);
        searchOverlapNodes(items, item, list);
        return list;
    }

}
