# MonoTransfer


MonoTransfer is a library for connecting simple controllers over a single wire

* Support  **all** arduino digital pins.
* Can be used without external crystal oscillator (tested with attiny85) with lower speed
* Speed up to **1600 baud** using atmega328


## How It Works

1. One board send data using users delays.
2. Another board read pin state depending on the timing and transform it to string
3. Every packet ends with symbol you define in class constructor


## Usage
### Wiring
You need 2 controllers and 1 resistor (10k recomended)
![Wiring](https://github.com/BLOTHDARM/MonoTransfer/blob/main/img/connection.png?raw=true)

### Configuring

Constructor need 3 arguments: arduino pin, standart delay (in microseconds default 1000) (lower value = higher speed), ending symbol.

<details><summary><b>Show example</b></summary>

```diff
MonoTransfer Seriall(5,1000,'-');
```
</details>

### Send/read
Sending and reading is as easy as configuration - use ```send()``` and ```String``` as argument.


<details><summary><b>Show example</b></summary>

```diff
Seriall.send("Test message");
```
</details>

Common code to obtain data will use ```available()``` and ```read()``` functions.
```available()``` returns ```true``` if data available and ```false``` if not.
```read()``` returns ```String``` with data


<details><summary><b>Show example</b></summary>

```diff
if(Seriall.available())
{
  String data = Seriall.read();
  Serial.print("data: ");
  Serial.println(data);
}
```
</details>
