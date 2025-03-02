![Banner](https://s-christy.com/sbs/status-banner.svg?icon=maps/design_services&hue=200&title=Design%20Patterns&description=23%20classic%20GoF%20patterns%20implemented%20in%20C%2B%2B)

## Overview

This repository contains implementations of all 23 classic Gang of Four (GoF)
design patterns in C++17. Each pattern is implemented as a self-contained
example in its own `.cpp` file, organized into the three canonical categories:
creational, structural, and behavioral. The examples use realistic scenarios to
illustrate how and why each pattern is applied.

## Patterns

### Creational

These patterns deal with object creation mechanisms, aiming to create objects
in a manner suitable to the situation.

| Pattern | Description |
|---|---|
| Abstract Factory | Creates families of related objects without specifying concrete classes |
| Builder | Separates complex object construction from its representation |
| Factory Method | Lets subclasses decide which class to instantiate |
| Prototype | Creates new objects by cloning an existing prototype |
| Singleton | Ensures a class has only one instance with a global access point |

### Structural

These patterns deal with object composition, creating relationships between
objects to form larger structures.

| Pattern | Description |
|---|---|
| Adapter | Converts one interface into another that clients expect |
| Bridge | Decouples an abstraction from its implementation |
| Composite | Composes objects into tree structures for part-whole hierarchies |
| Decorator | Attaches additional responsibilities to an object dynamically |
| Facade | Provides a simplified interface to a complex subsystem |
| Flyweight | Uses sharing to efficiently support large numbers of fine-grained objects |
| Proxy | Provides a surrogate to control access to another object |

## Usage

## License

This work is licensed under the GNU General Public License version 3 (GPLv3).

[<img src="https://s-christy.com/status-banner-service/GPLv3_Logo.svg" width="150" />](https://www.gnu.org/licenses/gpl-3.0.en.html)
