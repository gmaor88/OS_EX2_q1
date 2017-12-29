#ifndef ___POLYGON_H___
#define ___POLYGON_H___

/**************************************************/
///					Include						///
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/***************************************************/

/**************************************************/
///					Define						///
/**************************************************/
#define TRUE									1
#define FALSE									0
#define NUM_OF_VERTICES_IN_TRIANGLE				3
#define NUM_OF_VERTICES_IN_QUAD					4
#define ADD_POLYGON								0
#define PERIMETER								1
#define AREA									2
#define PRINT_POLYGON							3
#define DO_CURRENT								4
#define	DO_ALL									5
#define TRIANGLE								0
#define QUAD									4

/***************************************************/

/**************************************************/
///				MASKS And Shift					///
/**************************************************/
#define NEW_POLYGON_MASK						0x2
#define POLYGON_TYPE_MASK						0x4
#define ACTIONS_MASK							0x38
#define PRINT_ACTION_REQUESTED					8
#define PERIMITER_ACTION_REQUESTED				16
#define AREA_ACTION_REQUESTED					32
#define POLYGONS_TO_DO_ACTIONS_ON_MASK			0xc0
#define COORDINATES_MASK						0xFFF
#define COORDINATES_VALUE_MASK					0x3f
#define SIGN_BIT_MASK							0x20
#define NEGATIVE_BIT_MASK						0xFFC0
#define	SHIFT_TO_FIRST_VERTEX					8
#define SHIFT_TO_NEXT_VERTEX					12
#define SHIFT_TO_Y_VALUE						6
#define SHIFT_TO_GET_0_TO_4_VALUE				6

/***************************************************/

/**************************************************/
///				Typedef And Structs				///
/**************************************************/
typedef struct _vertex {
    int x, y;
} Vertex;

typedef struct _triangle {
    struct _vertex vertices[NUM_OF_VERTICES_IN_TRIANGLE];
} Triangle;

typedef struct _quad {
    struct _vertex vertices[NUM_OF_VERTICES_IN_QUAD];
} Quad;

typedef struct listNode {
    long long unsigned polygon;
    struct listNode* next;
}ListNode;

typedef struct list {
    ListNode* head;
    ListNode* tail;
}List;

/***************************************************/

/**************************************************/
///					Prototyps					///
/**************************************************/
int is_end_of_input(long long unsigned polygon);
void analyze_and_exec(long long unsigned polygon);
void free_list(void);

/***************************************************/
#endif
