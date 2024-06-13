#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10 // vertex(정점)의 최대 개수

/* git commit 용 수정 */

typedef struct node {
    int vertex; // vertex 0~9
    struct node *next; // 다음 노드
} Node;

typedef struct graph {
    Node *adjacentList[MAX_VERTEX]; // 인접리스트
    int visited[MAX_VERTEX]; // 방문한 정점
} Graph;

Graph* createGraph(); // 그래프 생성
void insertVertex(Graph *graph, int vertex);  // vertex 추가
void insertEdge(Graph *graph, int source, int destination);  // edge(간선) 추가
void printGraph(Graph *graph); // 그래프 출력
void depthFirstSearch(Graph *graph, int vertex); // DFS방식으로 그래프 탐색
void breathFirstSearch(Graph *graph, int startVertex); // BFS방식으로 그래프 탐색
void freeGraph(Graph *graph); // 그래프 메모리 해제
void resetVisited(Graph *graph); // visited 초기화

int main()
{ 
    printf("=== 2021041002 오원석 ===\n");
    printf("=== undirected graph use adjacent list ===\n\n");
    char command; // 입력한 키
    int key, source, destination; // key는 입력한 정점, source와 destination는 source와 destination으로 edge를 추가할 때 사용
    Graph* graph = NULL; //graph를 NULL로 설정

    do {
        printf("----------------------------------------------------------------\n");
        printf("                     Graph Searches                              \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph = z \n");
        printf(" Insert Vertex = v           Insert Edge = e \n");
        printf(" Depth First Search = d      Breath First Search = b\n");
        printf(" Print Graph = p             Quit = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
            case 'z': case 'Z':
                if (graph != NULL) {
                    freeGraph(graph); // 그래프에 메모리가 할당되어 있는 경우 메모리 해제
                }
                graph = createGraph(); // 그래프 생성
                break;
            case 'v': case 'V':
                if (graph == NULL) {
                    printf("Graph가 생성되지 않았습니다.\n"); // 그래프가 생성되지 않은 경우 오류 출력
                    break;
                }
                printf("Your Vertex = ");
                scanf("%d", &key); 
                insertVertex(graph, key); // vertex 추가
                break;
            case 'e': case 'E':
                if (graph == NULL) {
                    printf("Graph가 생성되지 않았습니다.\n"); // 그래프가 생성되지 않은 경우 오류 출력
                    break;
                }
                printf("Your Source Vertex = "); 
                scanf("%d", &source); // source vertex 입력
                printf("Your destinationination Vertex = ");
                scanf("%d", &destination); // destinationination vertex 입력
                insertEdge(graph, source, destination); // source와 destination vertex를 이용하여 edge 추가
                break;
            case 'd': case 'D':
                if (graph == NULL) {
                    printf("Graph가 생성되지 않았습니다.\n"); // 그래프가 생성되지 않은 경우 오류 출력
                    break;
                }
                printf("Your Start Vertex = ");
                scanf("%d", &key); // 시작 정점 입력
                resetVisited(graph); // visited 초기화
                depthFirstSearch(graph, key); // DFS방식으로 그래프 탐색
                printf("\n");
                break;
            case 'b': case 'B':
                if (graph == NULL) {
                    printf("Graph가 생성되지 않았습니다.\n"); // 그래프가 생성되지 않은 경우 오류 출력
                    break;
                }
                printf("Your Start Vertex = "); 
                scanf("%d", &key); // 시작 정점 입력
                resetVisited(graph); // visited 초기화
                breathFirstSearch(graph, key); // BFS방식으로 그래프 탐색
                printf("\n"); 
                break;
            case 'p': case 'P':
                if (graph == NULL) {
                    printf("Graph가 생성되지 않았습니다.\n"); // 그래프가 생성되지 않은 경우 오류 출력
                    break;
                }
                printGraph(graph); // 그래프 출력
                break;
            case 'q': case 'Q':
                freeGraph(graph); // 할당된 동적 메모리 해제
                break;
            default:
                printf("잘못된 명령어입니다.\n"); // 잘못된 명령어 입력시 오류 출력
                break;
        }
    } while (command != 'q' && command != 'Q'); // q나 Q가 입력되면 종료

    return 0;
}

Graph* createGraph() { 
    Graph *graph = (Graph*)malloc(sizeof(Graph)); // 그래프 생성
    for (int i = 0; i < MAX_VERTEX; i++) { // 0~9까지 반복
        graph->adjacentList[i] = NULL; // 인접리스트 초기화
        graph->visited[i] = 0; // visited 초기화
    }
    return graph;
}

void insertVertex(Graph *graph, int vertex) { // vertex 추가 함수
    if (vertex < 0 || vertex >= MAX_VERTEX) { 
        printf("vertex는 0~9사이 정수여야 합니다.\n"); // vertex가 0~9사이 정수가 아닌 경우 오류 출력
        return;
    }
    if (graph->adjacentList[vertex] != NULL) { 
        printf("Vertex %d 가 이미 존재합니다.\n", vertex); //해당 vertex가 이미 존재하는 경우 오류출력
        return;
    }
    graph->adjacentList[vertex] = (Node*)malloc(sizeof(Node)); // vertex에 대한 노드 생성
    graph->adjacentList[vertex]->vertex = vertex; // vertex를 vertex로 하는 노드 생성
    graph->adjacentList[vertex]->next = NULL; // 마지막 노드일 경우 NULL로 초기화
}

void insertEdge(Graph *graph, int source, int destination) { // edge 추가 함수
    if (source < 0 || source >= MAX_VERTEX || destination < 0 || destination >= MAX_VERTEX) { // vertex가 0~9사이 정수가 아닌 경우 오류출력
        printf("vertex는 0~9사이 정수여야 합니다.\n");
        return;
    }
    if (graph->adjacentList[source] == NULL || graph->adjacentList[destination] == NULL) { // vertex가 존재하지 않는 경우 오류출력
        printf("vertex가 존재하지 않습니다.\n");
        return;
    }
    Node *newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성
    newNode->vertex = destination; // destination를 vertex로 하는 노드 생성
    newNode->next = NULL; // 초기화

    if (graph->adjacentList[source]->next == NULL) { // source의 인접리스트가 비어있는 경우
        graph->adjacentList[source]->next = newNode; // 새로운 노드를 연결
    } 
    else { // source의 인접리스트가 비어있지 않은 경우
        Node *temp = graph->adjacentList[source]->next;  // temp를 source의 인접리스트의 첫번째 노드로 설정
        Node *prev = NULL; // 이전 노드를 NULL로 초기화
        while (temp != NULL && temp->vertex < destination) { // temp가 NULL이 아니고 temp의 vertex가 destination보다 작은 경우
            prev = temp; // prev를 temp로 설정
            temp = temp->next; // temp를 다음 노드로 설정
        }
        if (prev == NULL) { // prev가 NULL인 경우
            newNode->next = graph->adjacentList[source]->next; // newNode를 source의 인접리스트의 첫번째 노드로 설정
            graph->adjacentList[source]->next = newNode; // source의 인접리스트의 첫번째 노드를 새로운 노드로 설정
        } 
        else { // prev가 NULL이 아닌 경우
            newNode->next = prev->next; // newNode를 prev의 다음 노드로 설정
            prev->next = newNode; // prev의 다음 노드를 newNode로 설정
        }
    }

    // undirected graph이므로 destination에서 source로도 edge 추가
    newNode = (Node*)malloc(sizeof(Node)); // 새로운 노드 생성
    newNode->vertex = source; // source를 vertex로 하는 노드 생성
    newNode->next = NULL; // 초기화

    if (graph->adjacentList[destination]->next == NULL) { // destination의 인접리스트가 비어있는 경우
        graph->adjacentList[destination]->next = newNode; // 새로운 노드를 연결
    } 
    else { // destination의 인접리스트가 비어있지 않은 경우
        Node *temp = graph->adjacentList[destination]->next;  // temp를 destination의 인접리스트의 첫번째 노드로 설정
        Node *prev = NULL; // 이전 노드를 NULL로 초기화
        while (temp != NULL && temp->vertex < source) { // temp가 NULL이 아니고 temp의 vertex가 source보다 작은 경우
            prev = temp; // prev를 temp로 설정
            temp = temp->next; // temp를 다음 노드로 설정
        }
        if (prev == NULL) { // prev가 NULL인 경우
            newNode->next = graph->adjacentList[destination]->next; // newNode를 destination의 인접리스트의 첫번째 노드로 설정
            graph->adjacentList[destination]->next = newNode; // destination의 인접리스트의 첫번째 노드를 새로운 노드로 설정
        } 
        else { // prev가 NULL이 아닌 경우
            newNode->next = prev->next; // newNode를 prev의 다음 노드로 설정
            prev->next = newNode; // prev의 다음 노드를 newNode로 설정
        }
    }
}

void printGraph(Graph *graph) { // 그래프 출력 함수
    for (int i = 0; i < MAX_VERTEX; i++) { // 0~9까지 반복
        if (graph->adjacentList[i] != NULL) { // vertex가 존재하는 경우 
            Node *ptr = graph->adjacentList[i]->next; // ptr을 vertex의 인접리스트의 첫번째 노드로 설정
            printf("Vertex %d: ", i); 
            while (ptr) {   // ptr이 NULL이 아닌 경우
                printf("%d -> ", ptr->vertex); // ptr의 vertex 출력
                ptr = ptr->next; // ptr을 다음 노드로 설정
            }
            printf("NULL\n"); // 마지막 노드인 경우 NULL 출력
        }
    }
}

void depthFirstSearch(Graph *graph, int vertex) { // DFS방식으로 그래프 탐색
    Node *adjacentList = graph->adjacentList[vertex]->next; // vertex의 인접리스트의 첫번째 노드로 설정
    Node *temp = adjacentList; // temp를 adjacentList로 설정

    graph->visited[vertex] = 1; // vertex를 방문한 것으로 표시
    printf("%d -> ", vertex); // vertex 출력

    while (temp != NULL) { // temp가 NULL이 아닌 경우
        int connectedVertex = temp->vertex; // connectedVertex를 temp의 vertex로 설정

        if (graph->visited[connectedVertex] == 0) { // connectedVertex를 방문하지 않은 경우
            depthFirstSearch(graph, connectedVertex); // connectedVertex를 방문
        }
        temp = temp->next; // temp를 다음 노드로 설정
    }
}

void breathFirstSearch(Graph *graph, int startVertex) { // BFS
    int queue[MAX_VERTEX]; // 큐 생성
    int front = 0; // front 초기화
    int rear = 0; // rear 초기화

    graph->visited[startVertex] = 1; // startVertex를 방문한 것으로 표시 
    queue[rear++] = startVertex; // startVertex를 큐에 삽입 

    while (front < rear) { // front가 rear보다 작은 경우
        int currentVertex = queue[front++]; // currentVertex를 큐의 front로 설정 
        printf("%d -> ", currentVertex);

        Node *temp = graph->adjacentList[currentVertex]->next; // temp를 currentVertex의 인접리스트의 첫번째 노드로 설정

        while (temp) { // temp가 NULL이 아닌 경우
            int adjVertex = temp->vertex; // adjVertex를 temp의 vertex로 설정

            if (graph->visited[adjVertex] == 0) { // adjVertex를 방문하지 않은 경우
                queue[rear++] = adjVertex; // adjVertex를 큐에 삽입
                graph->visited[adjVertex] = 1; // adjVertex를 방문한 것으로 표시
            }
            temp = temp->next; // temp를 다음 노드로 설정
        }
    }
}

void resetVisited(Graph *graph) { // visited 초기화
    for (int i = 0; i < MAX_VERTEX; i++) { // 0~9까지 반복
        graph->visited[i] = 0; // visited를 0으로 초기화
    }
}

void freeGraph(Graph *graph) { // 그래프 메모리 해제
    if (graph == NULL) return;  // 그래프가 NULL인 경우

    for (int i = 0; i < MAX_VERTEX; i++) { // 0~9까지 반복
        Node *temp = graph->adjacentList[i];  // temp를 vertex의 인접리스트의 첫번째 노드로 설정
        while (temp) { // temp가 NULL이 아닌 경우
            Node *next = temp->next; // next를 temp의 다음 노드로 설정
            free(temp); // temp 메모리 해제
            temp = next; // temp을 next로 설정
        }
    }
    free(graph); // 그래프 메모리 해제
}


