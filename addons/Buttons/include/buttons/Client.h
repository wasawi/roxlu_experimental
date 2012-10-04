#ifndef ROXLU_BUTTONS_CLIENTH
#define ROXLU_BUTTONS_CLIENTH

#include <buttons/Types.h>
#include <buttons/Element.h>
#include <buttons/Server.h>

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <roxlu/Roxlu.h> 

// @todo set nodelay on socket

namespace buttons {
	/*
	enum ClientTaskName {
		 BCLIENT_PARSE_SCHEME
		 ,BCLIENT_SEND_TO_SERVER
			 ,BCLIENT_VALUE_CHANGED_SLIDERI
		 ,BCLIENT_VALUE_CHANGED_SLIDERF

	};


	struct ClientTask {
		ClientTask(ClientTaskName name)
			:name(name)
			,sliderf_value(0.0f)
			,slideri_value(0)
			,element(NULL)
			,sliderf(NULL)
			,buttons(NULL)
		{
		}

		ClientTaskName name;
		ButtonsBuffer buffer;
		Element* element;
		Sliderf* sliderf;
		Buttons* buttons;

		float sliderf_value;
		int slideri_value;
	};
	*/
	class Client : public roxlu::Runnable, public ButtonsListener {
	public:
		Client(const std::string ip, int port);
		~Client();
		void start();
		void run();

		void update();
		void draw();

		void onMouseDown(int x, int y);
		void onMouseUp(int x, int y);
		void onMouseMoved(int x, int y);

		void onEvent(ButtonsEventType event, const Buttons& buttons, const Element* target, void* targetData);
		void operator()(unsigned int dx); // operator for button clicks
	private:
		void clear(); // deletes all allocated guis and widgets and references
		bool connect();
		void parseBuffer();
		void getScheme(); // sends the command to retrieve the scheme
		void parseScheme(CommandData& cmd);

		void addInCommand(CommandData task);
		void addOutCommand(CommandData task); // will be name: addSendTask or something.

		void send(const char* buffer, size_t len); // send data to server
	private:
		bool is_connected;
		Socket sock;
		roxlu::Thread thread;
		roxlu::Mutex mutex;
		int port;
		std::string ip;
		ButtonsBuffer buffer;
		ClientServerUtils util;
		std::vector<CommandData> out_commands; // used for Client --> Server communication
		std::vector<CommandData> in_commands; // must be handle in own thread
		std::map<unsigned int, buttons::Buttons*> buttons; 
		std::map<unsigned int, std::map<unsigned int, buttons::Element*> > elements;

		// used on guis @todo when destrying deallocate thse
		std::vector<float*> value_floats;
		std::vector<int*> value_ints;
		std::vector<bool*> value_bools;
		std::vector<float*> value_float_arrays;
		std::vector<int*> value_int_arrays;
	};

} // buttons
#endif