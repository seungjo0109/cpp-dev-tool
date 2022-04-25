## Single responsibility principle

* Single Responsibility Principle(SRP) means each code unit should have exactly one responsibility.
* This means writing functions that do one thing only, creating tpyes that are responsibile for a single thing, and creating higher-level components that are focused on one aspect only.
* This means that if your class manages some type of resources, such as file handles, it should do only that, leaving parsing them, for example, to another type.

</br>

* Often, if you see a function with "And" in its name, it's violating the SRP and should be refactored.
* Anothrer sign is when a function has comments indicating what each section of the function(sic) does. Each such section would probably be better off as a distinct function.

</br>

* In its essence, it says that no object should know no more than necessary about other objects, so it doesn't depend on any of their internals.
* Applying it leads to more maintainable code with fewer interdependecies between components.


### reference: Software Architecture with C++: Design modern systems using effective architecture concepts, design patterns, and techniques with C++20