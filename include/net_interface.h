#ifndef NET_INTERFACE_H_INCLUDED
#define NET_INTERFACE_H_INCLUDED

class cNetInterface {
	private:

	public:
		cNetInterface();
		cNetInterface(int port);
		~cNetInterface();

		bool init_net(int port);
		void start_listening();

};

#endif // NET_INTERFACE_H_INCLUDED
