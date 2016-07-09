//malloc.c
#include "minicrt.h"

typedef struct _heap_header{
	enum{
		HEAP_BLOCK_FREE = 0xABABABAB,		//magic number of free block,空闲块的魔数
		HEAP_BLOCK_USED = 0xCDCDCDCD,		//magic number of used block
	}type;

	unsigned size;					//block size including header
	struct _heap_header* next;
	struct _heap_header* prev;
}heap_header;

#define ADDR_ADD(a,o)(((char*)(a))+o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header* list_header = null;

void free(void *ptr){
	heap_header* header = (heap_header*)ADDR_ADD(ptr,-HEADER_SIZE);
	if(header->type != HEAP_BLOCK_USED)
		return;

	header->type = HEAP_BLOCK_FREE;
	if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE){
		//merge
		header->prev->next = header->next;
		if(header->next!=NULL)
			header->next->prev = header->prev;
		header->prev->size+=header->size;

		header = header->prev;
	}

	if(header->next != NULL && header->next->type == HEAP_BLOCK_FREE){
		//merge
		header->size += header->next->size;
		header->next = header->next->next;
	}
}

void* malloc(unsigned size){
	heap_header *header;

	if(size==0)
		return NULL;

	header = list_header;
	while(header!=0){
		
	}
}

