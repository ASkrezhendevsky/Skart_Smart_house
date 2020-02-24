#ifndef LendthSensor_H
#define LendthSensor_H
class LendthSensor{
	
	public:
	int getLength();
	void setPin(int newPin);
	int getPin();
	
	private:
	int pin;
}

#endif