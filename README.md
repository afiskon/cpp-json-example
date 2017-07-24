# cpp-json-example

Simple example of working with JSON in C++.

How to build:

```
git submodule init
git submodule update
mkdir build
cd build
cmake ..
make
```

Example:

```
$ ./json_example
Id: 777123456789
Name: Aleksander Alekseev
Phone: 79161234567
--- Birthday ---
Year: 1988
Month: 8
Day: 5
----------------
Original object:
User(id = 777123456789, name = Aleksander Alekseev, phone = 79161234567, birthday = Date(year = 1988, month = 8, day = 5))
Serialized:
{
    "id": 777123456789,
    "name": "Aleksander Alekseev",
    "birthday": [
        1988,
        8,
        5
    ],
    "phone": 79161234567
}
Deserialized:
User(id = 777123456789, name = Aleksander Alekseev, phone = 79161234567, birthday = Date(year = 1988, month = 8, day = 5))
```
