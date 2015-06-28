#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;
struct a{
	int i=456;
	string str = string("123");
};
main(){
	a* aa = (struct a*)malloc(sizeof(struct a));
	//aa->str = string("abc");
	cout<< aa->i << endl;
	cout<< aa->str <<endl;
//	a bb;
//	bb.str = "cde";
//	cout<< bb.str <<endl;
}
