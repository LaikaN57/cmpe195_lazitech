#include "module.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Irlanda A <>");
MODULE_AUTHOR("Yasmine J <>");
MODULE_AUTHOR("Alex Kennedy <alexzanderkennedy@gmail.com>");
MODULE_DESCRIPTION("Module");
MODULE_VERSION("0:1.0.1");

int __init_or_module my_module_init(void) {
	static unsigned long once;

	if(test_and_set(0, &once)) {
		return -EBUSY;
	}

	return 0;
}

void __exit my_module_exit() {
}

module_init(my_module_init);
module_exit(my_module_exit);

