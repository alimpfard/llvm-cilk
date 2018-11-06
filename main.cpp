#include <iostream>
#include <fstream>
#include <unistd.h>
#include "AST_node.h"

using namespace std;
using namespace llvm;

extern FILE* yyin;
extern BlockExprNode* root;
extern int yyparse();
extern void linkExternalFunctions(GenContext &context);


void usage(char ch = 0) {
	if (ch)
		cout << "Invalid option " << ch << endl;
	cout << "\nusage: ./compiler [-fhpvd] <filename.c>\n" << endl;
	cout << "optional arguments:" << endl;
	cout << " -h\thelp" << endl;
	// cout << " -d\tyydebug = 1" << endl;
	cout << " -v\tshow output in terminal" << endl;
	cout << " -f\tshow output in *.ll or *.ctr" << endl;
	cout << " -p\toutput citron version" << endl;
	cout << " -m <func>\trun func instead of main" << endl;
}

int main(int argc, char **argv) {
	char *filename;
	bool f = false, p = false, v = false;
	char *mainfn = "main";
	// check args
	if (argc == 2)
		filename = argv[1];
	else if (argc >= 3) {
		filename = argv[argc-1];
		int ch;
		while((ch = getopt(argc, argv, "m:fhpvd")) != -1) {
			switch(ch) {
			case 'h':
				usage();
				return 0;
			case 'f':
				f = true;
				break;
			case 'p':
				p = true;
				break;
			case 'v':
				v = true;
				break;
			case 'd':
			#if YYDEBUG
				yydebug = 1;
			#endif
				break;
			case 'm':
				mainfn = optarg;
			break;
			default:
				usage(ch);
				return 0;
			}
		}
	} else {
		usage();
		return 0;
	}
	// check filename
	int len = strlen(filename);
	if (filename[len - 1] != 'c' || filename[len - 2] != '.') {
		usage();
		return 0;
	}
	yyin = fopen(filename, "r");
	if (!yyin) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
	if (yyparse()){
		cout << "ERROR!" << endl;
		return EXIT_FAILURE;
	}
	// implement options
	if (p) {
		GenContextP context;
		cout << "Generating citron code" << endl;
		cout << "----------------------" << endl;
		context.CodeGen(*root);
		cout << "----------------------" << endl;
		cout << "Finished" << endl;
		if (f) {
			filename[len-1] = 'c';
			filename[len] = 't';
			filename[len+1] = 'r';
			filename[len+2] = '\0';
			ofstream outfile;
			outfile.open(filename, ios::out);
			context.OutputCode(outfile);
			outfile.close();
		}
		if (v) {
			cout << "citron code:" << endl;
			cout << "------------" << endl;
			context.OutputCode(cout);
			cout << "------------" << endl;
			cout << "citron code ends" << endl;
		}
		cout << "+=====================================+" << endl;
		cout << "| To Run citron code, please use:     |" << endl;
		cout << "|      ctr c_code/<filename.ctr>      |" << endl;
		cout << "+=====================================+" << endl;
		cout << "finished" << endl;
	} else {
		GenContext context;
		InitializeNativeTarget();
		InitializeNativeTargetAsmPrinter();
		InitializeNativeTargetAsmParser();
		linkExternalFunctions(context);
		cout << "Generating LLVM code" << endl;
		cout << "--------------------" << endl;
		context.CodeGen(*root);
		cout << endl;
		cout << "--------------------" << endl;
		cout << "Finished" << endl;
		if (f) {
			filename[len-1] = 'l';
			filename[len] = 'l';
			filename[len+1] = '\0';
			ofstream outfile;
			outfile.open(filename, ios::out);
			context.OutputCode(outfile);
			outfile.close();
		}
		if (v) {
			cout << "LLVM code:" << endl;
			cout << "----------" << endl;
			context.OutputCode(cout);
			cout << "----------" << endl;
			cout << "LLVM code ends" << endl;
		}
		cout << "Run LLVM code" << endl;
		cout << "-------------" << endl;
		context.run(mainfn);
		cout << endl;
		cout << "-------------" << endl;
		cout << "Run LLVM code ends" << endl;
		cout << "Finished" << endl;
	}
	fclose(yyin);
	return 0;
}
