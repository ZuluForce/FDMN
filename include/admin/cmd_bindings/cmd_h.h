#ifndef CMD_H_H_INCLUDED
#define CMD_H_H_INCLUDED

#include <map>
#include <sstream>

using namespace std;

typedef void (*helpFn) (stringstream&);


struct treeLeaf {
	helpFn getHelp;
};

struct treeNode {
	treeNode** subNodes;
	treeLeaf* leaf;
};

treeNode* initCharTree();
void addStr(const char*);
void addStr(const string&);
void rmStr(const char*);
void rmStr(const string&);
helpFn getFn(const char*);
helpFn getFn(const string&);

class cHelpRegister {
	private:


	public:
		cHelpRegister();
		~cHelpRegister();
};

void eval_cmd_h(string cmd);
void print_help_h();

#endif // CMD_H_H_INCLUDED
