#ifndef __GOODS_INFO_H__

#define __GOODS_INFO_H__

#include "header.h"

typedef struct storage_goods_info{
	unsigned char goods_type;
	unsigned int goods_count;
}storage_goods_info;


//insert goods info   suc = true  failed = false
bool goods_insert(storage_goods_info goods);
//select goods info storage_goods_info suc 
storage_goods_info goods_select(unsigned goods_type);

#endif
