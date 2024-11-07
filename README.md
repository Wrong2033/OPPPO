# OPPPO
Добро пожаловать в систему управления транспортными средствами!

Эта программа позволяет добавлять, удалять и просматривать транспортные средства. 
Возможные команды:

1. **ADD <тип> <параметры>**:
   Добавляет новый объект транспортного средства в контейнер.
   - <тип> может быть: Truck, Bus, Car.
   - <параметры> зависят от типа:
     - Truck: <грузоподъемность> <мощность> <страна>
       Пример: ADD Truck 1500 250 USA
     - Bus: <пассажировместимость> <мощность> <страна>
       Пример: ADD Bus 40 300 Germany
     - Car: <количество дверей> <максимальная скорость> <мощность> <страна>
       Пример: ADD Car 4 180 150 Japan

2. **REM <условие>**:
   Удаляет объекты из контейнера, удовлетворяющие заданному условию.
   Условие состоит из <параметра>, <знака> и <значения>. Формат:
   <параметр> <знак> <значение>
   - Доступные параметры:
     - Для Truck: payload (грузоподъемность), power (мощность двигателя)
     - Для Bus: seats (пассажировместимость), power (мощность двигателя)
     - Для Car: doors (количество дверей), speed (максимальная скорость), power (мощность двигателя)
   - Доступные знаки:
     - > (больше)
     - < (меньше)
     - == (равно)
     - >= (больше или равно)
     - <= (меньше или равно)
   
   Пример: REM payload > 1000

3. **PRINT**:
   Выводит информацию обо всех транспортных средствах, находящихся в контейнере.

4. **HELP**:
   Показывает эту справочную информацию.

Примечание: Убедитесь, что вводите команды правильно, следуя указанному синтаксису. 

Пробуйте различные команды для добавления и удаления транспортных средств, и наблюдайте за изменениями в списке.
