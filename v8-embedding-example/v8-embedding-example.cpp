#include "pch.h"
#include "v8pp/context.hpp"
#include <libplatform/libplatform.h>
#include <v8.h>
#include <PathCch.h>
#include <iostream>

void runJavaScriptCode();

int main(int argc, char *argv[])
{
	v8::V8::InitializeExternalStartupData(argv[0]);

	auto platform = v8::platform::NewDefaultPlatform();
	v8::V8::InitializePlatform(platform.get());
	v8::V8::Initialize();

	runJavaScriptCode();

	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();

	return EXIT_SUCCESS;
}

void runJavaScriptCode()
{
	v8pp::context context;
	v8::HandleScope handleScope(context.isolate());

	auto result = context.run_script(
		"function fib(n) {"
			"if (n == 0) {"
				"return 0;"
			"}"
			"else if (n == 1) {"
				"return 1;"
			"}"

			"return fib(n - 1) + fib(n - 2);"
		"}"

		"fib(8);"
	);

	v8::String::Utf8Value resultString(context.isolate(), result);

	std::cout << "The result of the script was: " << *resultString << "\n";
}