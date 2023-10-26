### Reverse iterator

*Шаблон `std::reverse_iterator` - итераторный адаптер, позволяющий создавать обратные итераторы на основе обычных. Весь
его функционал заключается в подмене прямых проходов (`++`, `+=`) обратными (`--`, `-=`) и наоборот. Является
стандартным способом генерации обратных итераторов в контейнерах стандартной библиотеки*

##### Задание

Реализуйте шаблон `ReverseIterator`, аналог `std::reverse_iterator`, параметризованный типом итератора, со следующими
операциями:
* Конструктор по умолчанию;
* Конструктор от обычного итератора;
* Метод `Base()` - возвращает обычный итератор, хранимый в классе;
* Операция разыменовывания `*`;
* Операция `->`;
* Операция `[]`;
* Операции `++` и `--`;
* Операции `+=` и `-=`;
* Операции сравнения;
* Операция сложения и разности с числом;
* Операция разности двух итераторов.

Дополнительно реализуйте шаблонную функцию `MakeReverseIterator`, аналог `std::make_reverse_iterator`, которая принимает
произвольный итератор и возвращает соответствующий `ReverseIterator`.

Для указания корректных возвращаемых (и принимаемых) значений функций и методов вам может понадобиться класс.
`std::iterator_traits`.

**Напоминание:** итератор, который хранится в поле `std::reverse_iterator`, не совпадает с итератором на элемент, на
который реально указывает обратный итератор - он смещен на один элемент вправо. То есть, если обратный итератор
указывает на 5-й (с начала) элемент контейнера, то это значит, что у него в поле сохранен обычный итератор на 6-й
элемент. Это сделано для корректной реализации методов `rend()`. Контейнеры обязаны поддерживать реализацию элемента
"следующего за последним" (`end()`), но не обязаны поддерживать элемент "перед началом" (до `begin()`). Поэтому в
качестве `rend()` выступает сам `begin()`, а в качестве `rbegin()` - `end()`, то есть итераторы, смещенные на 1 вперед.
Учтите это при решении задания (в частности, при разыменовании нужно возвращать элемент перед текущим).