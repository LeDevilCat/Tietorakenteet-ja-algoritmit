#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "PostfixCalculator.h"

using namespace std;

string error_to_string(Error_code code) {
	switch (code) {
		case success:
			return "ok";
		case underflow:
			return "pinossa liian vahan alkioita";
		case divide_by_zero:
			return "nollalla jako ei ole sallittu";
		case bad_input:
			return "virheellinen syote";
		case invalid_operation:
			return "tuntematon operaatio";
		case overflow:
		default:
			return "laskinvirhe";
	}
}

Error_code run_token_stream(istream &input, PostfixCalculator &calculator) {
	string token;

	while (input >> token) {
		const Error_code code = calculator.process_token(token);
		if (code != success) {
			return code;
		}
	}

	return success;
}

int run_silent_mode() {
	PostfixCalculator calculator;
	const Error_code code = run_token_stream(cin, calculator);

	if (code != success) {
		cerr << "VIRHE: " << error_to_string(code) << endl;
		return 1;
	}

	Stack_entry value = 0.0;
	if (calculator.result(value) != success) {
		cerr << "VIRHE: tyhja pino" << endl;
		return 1;
	}

	cout << setprecision(15) << value << endl;
	return 0;
}

int run_prompt_mode() {
	PostfixCalculator calculator;

	cout << "PostFix-laskin (-p)" << endl;
	cout << "Syota postfix-lauseke. Komento q lopettaa." << endl;

	string line;
	while (true) {
		cout << "calc> ";
		if (!getline(cin, line)) {
			break;
		}

		if (line == "q" || line == "quit") {
			break;
		}

		calculator.reset();
		istringstream row(line);

		const Error_code code = run_token_stream(row, calculator);
		if (code != success) {
			cout << "VIRHE: " << error_to_string(code) << endl;
			continue;
		}

		Stack_entry value = 0.0;
		if (calculator.result(value) != success) {
			cout << "VIRHE: tyhja pino" << endl;
			continue;
		}

		if (calculator.stack_size() > 1) {
			cout << "VAROITUS: pinossa useita alkioita, tulostetaan huippu." << endl;
		}

		cout << "= " << setprecision(15) << value << endl;
	}

	return 0;
}

int main(int argc, char *argv[])
/*
Pre:   Program is started with optional command-line switch -p.
Post:  Evaluates postfix expression(s) and prints result or error.
Uses:  PostfixCalculator and Stack classes.
*/
{
	if (argc > 1 && string(argv[1]) == "-p") {
		return run_prompt_mode();
	}

	return run_silent_mode();
}
