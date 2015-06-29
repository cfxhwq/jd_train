#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;
int main(void){
	time_t now = time(NULL);
	cout<< "now is\t" << now <<endl;
	
	sleep(2);
	double sleep = difftime(time(NULL), now);
	cout<< "sleep\t" << sleep <<endl;

	struct tm* detail = gmtime(&now);
	cout<< "date:\tY" << detail->tm_year <<
		"M" << detail->tm_mon+1 << "D" << detail->tm_mday <<endl;
	cout<< "time:\tH" << detail->tm_hour << "M"
		<< detail->tm_min << "S" << detail->tm_sec <<endl;
	
	char* now_str = asctime(detail);
	cout<< "asctime:\t" << now_str <<endl;
	
	now_str = ctime(&now);//equal to asctime(localtime(now))
	cout<< "ctime:\t" << now_str <<endl;
	
	detail = localtime(&now);
	cout<< "local date:\tY" << detail->tm_year <<
		"M" << detail->tm_mon+1 << "D" << detail->tm_mday <<endl;
	cout<< "local time:\tH" << detail->tm_hour << "M"
		<< detail->tm_min << "S" << detail->tm_sec <<endl;

	now = mktime(detail);
	cout<< "tm to time_t\t" << now <<endl;

	char* buf;
	strftime(buf, 256, "%A %d %B, %I:%S:%P", detail);
	cout<< "strftime:\t" << buf <<endl;

	
	now_str[23] = '6';
	if(strptime(now_str, "%a %b %d %H:%M:%S %Y\n\0", detail) == NULL){
		cerr<< "strptime error" <<endl;
	}
	else{
		cout<< "strptime date:\tY" << detail->tm_year <<
			"M" << detail->tm_mon+1 << "D" << detail->tm_mday <<endl;
		cout<< "strptime time:\tH" << detail->tm_hour << "M"
			<< detail->tm_min << "S" << detail->tm_sec <<endl;
	}
}
