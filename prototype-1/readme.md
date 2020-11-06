# Prototype 1

The goal for this prototype is for validating the concepts/ assumptions related to hardware, only focusing on the disconnected version

## Test plan
---
### The Accuracy of local weather information VS HKO data
#### Assumption: 
The HKO data can only show marco climate but not focusing on relatively small geolocation
#### Expectation: 
- The prototype 1 can provide the micro climate data which should be slightly different from the HKO one
- The data could help on user making daily life decision (What to wear or when to do laundry)
#### Design:
A temperature/ humidity sensor, DHT 22 is connected to the system and it should provide a reading to Serial output every 4 seconds
#### Testing set up:
In an outdoor enviroment, we adopt 3 set of testing probes for comparison:
1. the prototype 1
2. The HKO data (scope down the data to district level)
3. Physical thermometer & humidity meter (Control)

#### Result:
Success, the the prototype 1's data is fulfilling our expectation

Testing datetime: 30/10/2020 13:33 @PolyU V core

| Test unit  | Temperature () | Humidity |
| ------------- | ------------- | ------------- |
| Prototype 1  | 29.0  | 60.6  |
| HKO data  | 26.3  | 73  |
|  Physical thermometer & humidity meter | 29  | 55  |


![Test 1 data result](https://github.com/hhhlau/SD5509-prototyping-and-scripting-2020/blob/main/prototype-1/assets/test1DataResult.jpg)
#### Technical Finding:
- HKO data can only reflecting a relatively large area (district level), but not minor climate
- The prototype 1 has to be connected the a power source, a battery-powered system would be better
- A housing for prototype 1 is be good to have

### User Finding
- The sight difference (+- 5%) in temperature/ humidity is not that useful -> I have not feeling with the figure
- "Sometime I may feel hot/ windy if I just referencing HKO temperature data, but this is not often. But I always feel cold but I don't have a jacket with me when I am visiting different indoor venues, even taking a bus."
- User don't reference to the weather often when doing laundry, just not raining will be fine. Typical HKers will have dehumidifier at home. 
---
### The compatibility of capturing user feedback 
Assumption: User would like to give feedback about the level of comfort if they are provided a chance
#### Expectation: 
The prototype 1 can capture the user feedback

#### Design: 
For this prototype, we would like to capture 2 data from user: "Too cold" & "Too hot". We set up 2 push buttons in the system as for the purpose.

#### Testing set up:
When user is pressing either of the buttons, the system should provide a Serial output: "User felt too hot." or "User felt too cold" coorespondingly.

#### Result:
Failed, the push buttons we had are for soidering use, we can't use it on a breadboard.
![Incorrect SMD push btn](https://github.com/hhhlau/SD5509-prototyping-and-scripting-2020/blob/main/prototype-1/assets/IMG_0093.jpeg)

#### Finding:

- The button signals are "bouncing" even with just a single press, a debounce treatment is needed 
- Users suggested we may added the third button "Just right" for providing us a more comphersive understanding on user's comfort


---
### Notification/ alert about humidity (Technical focus)
#### Assumption: 
If the humidity passed a designated point, an alert should be triggered
Expectation: The prototype 1 should be show an alert if the humidity passed the designated point

#### Design:
For this prototype, we selected LED light as our primary feedback channel as we wish to focus on hardware in this prototype. A 3-channels LED light is used for representing 3 staging of humidity:
Red: humidity > 55% 
Green: 45% < humidity < 55% (optimal humidity for human)
Blue: humidity < 45%

#### Testing set up:
For this test case, we need a dramatical change in humidity within a short period of time as to provide a controlable testing enviroment. Hence, we used a cup of hot water (w/ cover) and the hardware setup of Prototype 1. When the system is warmed up with a stable humidity reading, we put the cup's cover near the DHT 22 as for providing a sudden increase in humidity.

#### Result:
Success, the LED turned from green to red with the humidity reading rise to 60%+.
![System just run in](https://github.com/hhhlau/SD5509-prototyping-and-scripting-2020/blob/main/prototype-1/assets/IMG_0090.jpeg)
![Sudden change in humdity](https://github.com/hhhlau/SD5509-prototyping-and-scripting-2020/blob/main/prototype-1/assets/IMG_0091.jpeg)



----
[Repository ref./ Visual testing plan](https://github.com/hhhlau/SD5509-prototyping-and-scripting-2020/tree/main/prototype-1)
