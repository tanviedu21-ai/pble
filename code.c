Ved Lad:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOCATIONS 20
#define INF 999999

int n = 0;
char locations[MAX_LOCATIONS][50];
int adjMatrix[MAX_LOCATIONS][MAX_LOCATIONS];
int source = -1;

int dist[MAX_LOCATIONS];
int parent[MAX_LOCATIONS];
int visited[MAX_LOCATIONS];
int calculated = 0;

void enterGraph() {
printf("\nEnter the number of locations in the campus: ");

if (scanf("%d", &n) != 1  n <= 0  n > MAX_LOCATIONS) {
printf("Invalid number of locations. Setting to 0.\n");
n = 0;
return;
}

while (getchar() != '\n');

printf("\n--- Enter Location Names ---\n");

for (int i = 0; i < n; i++) {
printf("Location %d: ", i + 1);

fgets(locations[i], 50, stdin);

locations[i][strcspn(locations[i], "\n")] = '\0';
}

printf("\n--- Enter Adjacency Matrix ---\n");
printf("Enter distance between locations.\n");
printf("Enter -1 if there is NO direct connection.\n");
printf("Diagonal elements should be 0.\n\n");

for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {

int w;

printf("Distance from '%s' to '%s': ",
locations[i], locations[j]);

scanf("%d", &w);

if (i == j) {
adjMatrix[i][j] = 0;
}
else if (w == -1) {
adjMatrix[i][j] = INF;
}
else if (w < -1) {
printf("Weights cannot be negative. Setting to INF.\n");
adjMatrix[i][j] = INF;
}
else {
adjMatrix[i][j] = w;
}
}
}

calculated = 0;
source = -1;

printf("\nCampus graph entered successfully!\n");
}

void displayMatrix() {

if (n == 0) {
printf("\nGraph is empty. Please enter the campus graph first.\n");
return;
}

printf("\n--- Adjacency Matrix ---\n\t");

for (int i = 0; i < n; i++) {
printf("L%d\t", i + 1);
}

printf("\n");

for (int i = 0; i < n; i++) {

printf("L%d\t", i + 1);

for (int j = 0; j < n; j++) {

if (adjMatrix[i][j] == INF) {
printf("INF\t");
}
else {
printf("%d\t", adjMatrix[i][j]);
}
}

printf("\n");
}
}

void selectSource() {

if (n == 0) {
printf("\nGraph is empty. Please enter the campus graph first.\n");
return;
}

printf("\n--- Select Source Location ---\n");

for (int i = 0; i < n; i++) {
printf("%d. %s\n", i + 1, locations[i]);
}

printf("Enter choice (1-%d): ", n);

int choice;
scanf("%d", &choice);

if (choice >= 1 && choice <= n) {

source = choice - 1;
calculated = 0;

printf("Source selected as: %s\n", locations[source]);
}
else {
printf("Invalid selection.\n");
}
}

int getMinVertex() {

int min = INF;
int min_index = -1;

for (int v = 0; v < n; v++) {

if (!visited[v] && dist[v] <= min) {
min = dist[v];
min_index = v;
}
}

return min_index;
}

void findShortestDistance() {

if (n == 0) {
printf("\nGraph is empty. Please enter the campus graph first.\n");
return;
}

if (source == -1) {
printf("\nSource location not selected. Please select a source first.\n");
return;
}

// Initialization
for (int i = 0; i < n; i++) {

dist[i] = INF;
visited[i] = 0;
parent[i] = -1;
}

dist[source] = 0;

// Dijkstra's Algorithm
for (int count = 0; count < n - 1; count++) {

int u = getMinVertex();

if (u == -1)
break;

visited[u] = 1;

for (int v = 0; v < n; v++) {

if (!visited[v] &&
adjMatrix[u][v] != INF &&
dist[u] != INF &&
dist[u] + adjMatrix[u][v] < dist[v]) {

dist[v] = dist[u] + adjMatrix[u][v];

Ved Lad:
parent[v] = u;
}
}
}

calculated = 1;

printf("\nShortest distances calculated successfully using Dijkstra's Algorithm.\n");
}

void printPathRec(int j) {

if (parent[j] == -1) {
printf("%s", locations[j]);
return;
}

printPathRec(parent[j]);

printf(" -> %s", locations[j]);
}

void displayShortestPaths() {

if (!calculated) {
printf("\nDistances not calculated yet. Please run option 4 first.\n");
return;
}

printf("\n--- Shortest Paths from %s ---\n",
locations[source]);

printf("%-20s | %-16s | %s\n",
"Destination",
"Shortest Distance",
"Shortest Path");

printf("--------------------------------------------------------------------------------\n");

for (int i = 0; i < n; i++) {

if (i == source)
continue;

printf("%-20s | ", locations[i]);

if (dist[i] == INF) {

printf("%-16s | Unreachable\n", "INF");
}
else {

printf("%-16d | ", dist[i]);

printPathRec(i);

printf("\n");
}
}
}

void displayDistances() {

if (!calculated) {
printf("\nDistances not calculated yet. Please run option 4 first.\n");
return;
}

printf("\n--- Distances from %s to All Locations ---\n",
locations[source]);

for (int i = 0; i < n; i++) {

if (dist[i] == INF) {
printf("%s: INF (Unreachable)\n",
locations[i]);
}
else {
printf("%s: %d\n",
locations[i],
dist[i]);
}
}
}

int main() {

int choice;

do {

printf("\n========================================\n");
printf(" Campus Shortest Route Finder\n");
printf("========================================\n");

printf("1. Enter Campus Graph\n");
printf("2. Display Adjacency Matrix\n");
printf("3. Select Source Location\n");
printf("4. Find Shortest Distance (Dijkstra)\n");
printf("5. Display Shortest Paths\n");
printf("6. Display Distance from Source to All Locations\n");
printf("7. Exit\n");

printf("----------------------------------------\n");
printf("Enter your choice: ");

if (scanf("%d", &choice) != 1) {

printf("Invalid input! Exiting...\n");
break;
}

switch (choice) {

case 1:
enterGraph();
break;

case 2:
displayMatrix();
break;

case 3:
selectSource();
break;

case 4:
findShortestDistance();
break;

case 5:
displayShortestPaths();
break;

case 6:
displayDistances();
break;

case 7:
printf("\nExiting the program. Goodbye!\n");
exit(0);

default:
printf("\nInvalid choice! Please select an option between 1 and 7.\n");
}

} while (1);

return 0;
}
