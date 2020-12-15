```shell
list_entry 								#获得节点对应的入口
list_first_entry 						#获得第一个入口
list_last_entry 						#获得最后一个入口
list_first_entry_or_null 				#获得第一个入口或 NULL
list_next_entry 						#获得下一个入口
list_prev_entry 						#获得前一个入口
list_for_each							#正序遍历所有节点
list_for_each_prev						#倒叙遍历所有节点
list_for_each_safe						#安全正序遍历所有节点
list_for_each_prev_safe					#安全倒叙遍历所有节点
list_for_each_entry						#正序遍历所有入口
list_for_each_entry_reverse				#倒叙遍历所有入口
list_prepare_entry						#获得指定入口
list_for_each_entry_continue			#从指定入口开始正序遍历剩余的入口
list_for_each_entry_continue_reverse 	#从指定入口开始倒叙遍历剩余的入口
list_for_each_entry_from				#从指定入口正序遍历剩余入口
list_for_each_entry_from_reverse		#从指定入口倒序遍历剩余入口
list_for_each_entry_safe				#安全正序遍历所有入口
list_for_each_entry_safe_continue		#安全从指定入口正序遍历剩余入口
list_for_each_entry_safe_from			#安全从指定入口正序遍历剩余入口
list_for_each_entry_safe_reverse		#安全从指定入口倒序遍历剩余入口
list_safe_reset_next					#安全获得下一个入口
```
带safe的有什么区别?

```c
/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:        the type * to use as a loop cursor.
 * @head:       the head for your list.
 * @member:     the name of the list_head within the struct.
 */
#define list_for_each_entry_reverse(pos, head, member)                  \
        for (pos = list_last_entry(head, typeof(*pos), member);         \
        ¦    &pos->member != (head);                                    \
        ¦    pos = list_prev_entry(pos, member))


/**
 * list_for_each_entry_safe_reverse - iterate backwards over list safe against removal
 * @pos:        the type * to use as a loop cursor.
 * @n:          another type * to use as temporary storage
 * @head:       the head for your list.
 * @member:     the name of the list_head within the struct.
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 */
#define list_for_each_entry_safe_reverse(pos, n, head, member)          \
        for (pos = list_last_entry(head, typeof(*pos), member),         \
                n = list_prev_entry(pos, member);                       \
        ¦    &pos->member != (head);                                    \
        ¦    pos = n, n = list_prev_entry(n, member))


可以看到list_for_each_entry_reverse有三个参数,pos, head 和 name(pos中的名字).
对于list_for_each_entry_safe_reverse,多了一个n,临时存储pos前一个成员.每次遍历是
将n赋值给pos,这样遍历和pos关系就不大,在遍历过程中可以删除pos.
```

