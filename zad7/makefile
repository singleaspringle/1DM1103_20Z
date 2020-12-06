all:
	cc baza.c main.c -o mydb -Wall --pedantic

test-list: all
	./mydb baza.csv list_students
	./mydb baza.csv list_courses
	./mydb baza.csv list_grades

test-ile: all
	./mydb baza.csv count_students
	./mydb baza.csv count_courses
	./mydb baza.csv count_grades
	./mydb baza.csv course_grades 1DA1245

test-memory: all
	valgrind ./mydb baza.csv course_grades 1DA1245

test-add: all
	./mydb baza.csv add_course 1DM1103 Podstawy_programowania 2020Z
	./mydb baza.csv add_student Bartosz Staszynski 112233 bart@osz.pl
	./mydb baza.csv add_student_to_course 112233 1DM1103

test-set_grade: all
	./mydb baza.csv set_grade 1DM1103 112233 5.0 Super_praca_domowa

test-srednie: all
	./mydb baza.csv student_average 000007
	./mydb baza.csv course_average 1DA1245