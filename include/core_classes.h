#ifndef CORE_CLASSES_H_INCLUDED
#define CORE_CLASSES_H_INCLUDED

class cCoreModule {
	public:
		virtual void status(stringstream&) = 0;
		virtual void cleanup() = 0;
};

#endif // CORE_CLASSES_H_INCLUDED
