struct Segment {
    int sum, lazy;
} segm_tree[2 * N];

void propagate(int node, int left, int right) {
    //calculate the sum of the current node by adding lazy to all elements from left to right
    segm_tree[node].sum += (right - left + 1) * segm_tree[node].lazy;
    //pass the lazy to node's sons if it is not a leaf
    if (left < right) {
        segm_tree[2 * node + 1].lazy += segm_tree[node].lazy;
        segm_tree[2 * node + 2].lazy += segm_tree[node].lazy;
    }
    //since the node is now up-to-date, lazy becomes 0
    segm_tree[node].lazy = 0;
}

void update(int node, int left, int right, int x, int y, int value) {
    propagate(node, left, right);
    if (x <= left && right <= y) {
        segm_tree[node].lazy += value;
    } else {
        int middle = (left + right) / 2;
        if (x <= middle) {
            update(2 * node + 1, left, middle, x, y, value);
        }
        if (y >= middle + 1) {
            update(2 * node + 2, middle + 1, right, x, y, value);
        }
        //we need to call propagate on the sons here, as we use them to update the current node
        //so they must be up-to-date
        propagate(2 * node + 1, left, middle);
        propagate(2 * node + 2, middle + 1, right);
        segm_tree[node].sum = segm_tree[2 * node + 1].sum + segm_tree[2 * node + 2].sum;
    }
}

int query(int node, int left, int right, int x, int y) {
    propagate(node, left, right);
    if (x <= left && right <= y) {
        return segm_tree[node].sum;
    } else {
        int sum = 0;
        int middle = (left + right) / 2;
        if (x <= middle) {
            sum += query(2 * node + 1, left, middle, x, y);
        }
        if (y >= middle + 1) {
            sum += query(2 * node + 2, middle + 1, right, x, y);
        }
        return sum;
    }
}
