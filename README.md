Данный пет-проект представляет собой небольшую имитацию 3D-программы с возможностью добавлять объекты и проводить над ними типовые операции.</br>
Разрабатывается исключительно в познавательно-развлекательных целях.</br>
Аббревиатура CAD в названии условная, так как изначально это подразумевался прототип 3D-САПР,</br>
но на данный момент больше напоминает 3D редактор общего назначения.</br>

Стек: C++, OpenGL, Qt.

Основной интерфейс программы</br>
<img width="1577" height="955" alt="изображение" src="https://github.com/user-attachments/assets/f233c19a-24fa-4f34-b7bf-895497e966a0" /></br>
<img width="1593" height="990" alt="addcubeanimation" src="https://github.com/user-attachments/assets/d4b12ec7-6d73-42f7-93dd-31afea9d997b" /></br>
На изображении представлен вьюпорт, вращение и масштабирование камеры.</br>
Однако на данный момент задача разработки качественного UI/UX где-то на последнем месте.</br>

Реализованы классические Gizmo-операции:</br>
Перемещение</br>
<img width="1593" height="990" alt="translate" src="https://github.com/user-attachments/assets/5aa95fef-61fa-473b-a751-cb368e0375cd" /></br>
Вращение (нуждается в доработке)</br>
Во избежание gimbal lock используются кватернионы</br>
<img width="1593" height="990" alt="rotate" src="https://github.com/user-attachments/assets/a12eced5-ad33-4194-9849-7fff37884ea9" /></br>
Масштабирование</br>
<img width="1593" height="990" alt="scale" src="https://github.com/user-attachments/assets/237f8a28-b4a1-45ca-9429-85e86983d33b" /></br>
Выбор объекта на экране производится с помощью метода ray casting и AABB-ray intersection. 

Undo/Redo</br>
<img width="1593" height="990" alt="undoredo" src="https://github.com/user-attachments/assets/697c078d-3bab-4fd1-be7d-28749cbb3cb2" /></br>

Добавление другого объекта - цилиндр, и манипуляции с ними.</br>
<img width="1593" height="990" alt="addcylinder" src="https://github.com/user-attachments/assets/1a791b21-0ae8-4a45-abd1-6da80bf8451e" /></br>

Следующие планируемые этапы:
1. реализация булевых операций
2. ввод новых объектов
3. приближение интерфейса ближе к САПР-подобным программам с (около)точной настройкой размеров в реальных масштабах
4. возможно, добавление источников света
