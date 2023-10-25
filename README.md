# IR-Remote-Control-Bot
The Bot is controlled through IR remote. The project is slightly more enumerable than available in YouTube Videos or in any online articles. The project is developed on recent  version of IR_Remote Library of Arduino.
![IR_Bot_image](https://github.com/Aarid696/IR-Remote-Control-Bot/assets/79322886/58094a5f-dfee-4221-94f9-77a494292bf2)

# Working Procedure
1. Follow the circuit digram and simulation for wire connection. For connection of motor driver module _Check the pins of motor driver module from board with driver IC in simulation_ it is easy and simple. No need to worry! We could have used _Driver Module_ but it was not available in the TinkerCad, hence we used _driver IC_ for proper simulation. 
2. Downlaod the _decoder_file.ino_ in the Arduino Uno and find out the codes for the buttons of the IR_Remote. In our case we used button '2' for _forward_, button '6' for _left_, button '8' for _back_ and button 4'' for _right_ in the remote. 'Power' button for _stop_ command.
3. Download the _Main_control.ino_ in the Arduino UNO. Before downlaoding, update the remote codes _(where ever mentioned in the program)_ because it is unique.
4. Now you can play with the Bot!

# Problems faced and solution
1. **Decoding Problem:**
The very first problem that we faced was about decoding the hexadecimal code for the IR transmitter. In most of the YouTube Videos that provides the tutorial for the IR Remote Control car does not deals with the newer IR_Remote library for the Arduino IDE. While decoding the signals for the buttons of the IR remote, the values received were alphanumeric. But in YouTube tutorials the values receieved were of the kind _long int_. The decoding values may differ for various IR remotes, the values may differ due various configuartions for multiplexers and demultiplexers embedded in control circuit _(in this case it was Arduino UNo R3)_, the values may also differ for different IR_remote libraries and the last reason for the change may be due to electronic noise interference. So, the codes that were provided by the YouTube tutorials were subjected to _long int_ values but in our case we received alphanumeric values. To eradicate the issue, the alphanumeric codes were stored in string and then comparions were drawn.
3. **Motor Driver Circuit:**
We used the _L293N motor module_ for driving the motor. You may use any such configuations for driving the motor. Always the check the circuit diagram for the ICs, it will help you to know the connections better. You can either use _L293 IC_ or the entire module for the make. The simulation is made on the Ic but we have used the module for proper wiring and control. In our module the _enables pin A and B_ were not shot to the _5V_ power. It was independent and grounded. The first thing after buying the module you need to check the _enable pins_. These pins are reponsible fpr the speed control of the motor and takes digital value from 0 to 255. If the pins are grounded through jumpers, you need to remove it. Also check whether it is shot to the 5V or not, it it not then you need to provide digital signals to the pins while driving, and if it is shotted then withoug giving any signal by default it will work.
4. **Power Issue:**
This was prolonged issues that we faced, and most of the electronics engineers' task is solve this issue. The motor driver module is a current amplifier based hence it requires appreciable current in milli amps for driving the motors. We were using BO motors mechanised with gears, these are basically dc series motor. Initially we were giving power from motor driver side and it was then passing it to the arduino for the control. In most of the YouTube tutorials you will see this powering method. I will personally don't recommend this method. It is better to use different power modes separatley for arduino and motor driver respectively. Remember to make common grounds for both. The problem that we faced was when we were taking power from the motor driver side, the _5V pin_ of the driver is connected to the _Vin_ of the arduino. The _Vin_ is reponsible for the powering the arduino from external fluctuating power source. It works well when power requirement is less but not in this case where power requrement was more. Since were powering separatley for Arduino UNO R3 and Motor Driver, the _5V pin_ of the driver was connected to _5V pin_ of the Arduino so as to create the balance.

# Providing the Circuit Diagram

![IR Control Bot](https://github.com/Aarid696/IR-Remote-Control-Bot/assets/79322886/5e7644ff-2eb7-4527-b347-8e9741704fa3)

# Providing the Online Simulation of the model in TinkerCad
https://www.tinkercad.com/things/iiatNcfxgB7?sharecode=lZWnj-Vrb6yM29YGcNTwWRZlOoy62q2tkW0FbuxOUZE
