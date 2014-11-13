// #include <iostream>
// #include <fstream>
// #include <string>
// #include <cstring>

// #include "lib/gason/gason.h"

// using namespace std;


// double sum_and_print(JsonValue o);

// int main2() {

//     ifstream FILE_IN("sampleJson.in");
//     string ss;

// 	getline(FILE_IN, ss);

//     char * source = (char*) ss.c_str();
//     // do not forget terminate source string with 0
//     char * endptr = source + ss.length();
// 	JsonValue value;
// 	JsonAllocator allocator;
// 	int status = jsonParse(source, &endptr, &value, allocator);
// 	if (status != JSON_OK) {
// 		fprintf(stderr, "%s at %zd\n", jsonStrError(status), endptr - source);
// 		exit(EXIT_FAILURE);
// 	}


// 	cout << sum_and_print(value) << endl;

// }


// double sum_and_print(JsonValue o) {
//     double sum = 0;
//     switch (o.getTag()) {
//     case JSON_NUMBER:
//         sum += o.toNumber();
//         break;
//     case JSON_STRING:
//         break;
//     case JSON_ARRAY:
//         for (auto i : o) {
//             sum += sum_and_print(i->value);
//         }
//         break;
//     case JSON_OBJECT:
//         for (auto i : o) {
//             sum += sum_and_print(i->value);
//         }
//         break;
//     case JSON_TRUE:
//         break;
//     case JSON_FALSE:
//         break;
//     case JSON_NULL:
//         break;
//     }
//     return sum;
// }