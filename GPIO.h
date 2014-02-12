#ifndef GPIO_H
#define GPIO_H

class GPIO {
	public:
		enum direction {
		     in,
		     out,
			 none
		};
		enum level {
		     low,
		     high,
			 unkown
		};
		GPIO();
		GPIO (int pin);
		GPIO (int pin, direction dir);
		~GPIO();
		GPIO::level read();
		void write (GPIO::level l);
		void setDirection (GPIO::direction d);
		void setInput();
		void setOutput();
		void setPin (int pin);
		void unsetPin(int pin);
		int getPin();
		GPIO::direction getDirection();
	protected:
		int pin;
		direction dir;
		bool exported;
};

#endif // GPIO_H
