int
main (void)
{
	// dual buffer system

	// load file

	// execute LTO
	// swap buffers
	// execute next LTO
	// swap buffers
	// ...
	// no LTOs modified anything, break

	// store file

	// do nothing
	return 0;
}
