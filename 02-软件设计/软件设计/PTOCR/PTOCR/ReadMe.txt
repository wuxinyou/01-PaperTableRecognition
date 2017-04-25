
PTOCR
20170425
各个模块参见：方案验证里例程

1.添加readXML成功，这里是直接添加的源文件，不是静态库，注意与方案验证里例程的区别。
2.添加fileOpera成功，可以实现文件目录的查找
3.添加ExcelOpera成功，可以实现excel文件的操作
4.添加ProcessImage成功，可以实现图像处理，以及Tesseract识别，这里有个问题
	tesseract::TessBaseAPI tessOCR;不能放在成员变量中去，
	实际上是#include "include\\baseapi.h"
	#include "include\\strngs.h"
	不能放在头文件中，
	原因不详。
5.添加recognizeBar成功，可以识别条形码。
问题：有的时候编译会出一些报错，但是重新编译后会编译通过。