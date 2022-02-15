/*
 * @Author: your name
 * @Date: 2022-02-15 13:28:57
 * @LastEditTime: 2022-02-15 14:13:47
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /SkipList/go/ExampleSkipList.go
 */
package SkipList

import "fmt"

func ExampleSkipList() {
	sl := New()

	sl.Insert(float64(100), "foo")

	e := sl.Search(float64(100))
	fmt.Println(e.Value)
	e = sl.Search(float64(200))
	fmt.Println(e)

	sl.Insert(float64(20.5), "bar")
	sl.Insert(float64(50), "spam")
	sl.Insert(float64(20), 42)

	fmt.Println(sl.Len())
	e = sl.Delete(float64(50))
	fmt.Println(e.Value)
	fmt.Println(sl.Len())

	for e := sl.Front(); e != nil; e = e.Next() {
		fmt.Println(e.Value)
	}
	// Output:
	// foo
	// <nil>
	// 4
	// spam
	// 3
	// 42
	// bar
	// foo
}
