#include <stdbool.h>
#include <stdio.h>

bool all_received(bool received[], int total_nodes) {
  for (int i = 0; i < total_nodes; i++) {
    if (!received[i]) {
      return false;
    }
  }
  return true;
}

void one_to_all_Broadcast(int source_node, int total_nodes) {

  bool received[total_nodes];

  int p_node = (source_node + total_nodes / 2) % total_nodes;
  int p2 = (source_node + total_nodes / 4) % total_nodes;

  printf("Node %d Send message to Node %d\n", source_node, p_node);
  received[p_node] = true;

  printf("Node %d Send message to Node %d\n", source_node, p2);
  printf("Node %d Send message to Node %d\n", p_node, p2);
  received[p2] = true;

  for (int i = (p2 + 1) % total_nodes; i != source_node;
       i = (i + 1) % total_nodes) {
    printf("Node %d Send message to Node %d\n", source_node, i);
    printf("Node %d Send message to Node %d\n", p_node, i);
    printf("Node %d Send message to Node %d\n", p2, i);
    received[i] = true;

    if (all_received(received, total_nodes)) {
      break;
    }
  }

  printf("Communication Completed.\n");
}

int main() {
  int total_nodes, source_node;
  printf("Enter total number of nodes: ");
  scanf("%d", &total_nodes);

  printf("Enter source node (0 to %d): ", total_nodes - 1);
  scanf("%d", &source_node);

  one_to_all_Broadcast(source_node, total_nodes);

  return 0;
}
