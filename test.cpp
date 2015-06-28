#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;
struct a{
	string str;
};
main(){
	a* aa = (struct a*)malloc(sizeof(struct a));
	aa->str = string("abc");
	cout<< aa->str <<endl;
	//delete str;
}
