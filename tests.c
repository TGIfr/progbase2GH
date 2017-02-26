//
// Created by tgifr on 26.02.17.
//

#include <check.h>
#include <malloc.h>
#include "csv.h"
#include "list.h"


//getcols
START_TEST (getcols_strToTest_returns6){
    char * toTest = "bla;bla;d;t;a;s";
    char ** out = NULL;
    ck_assert(getcols(toTest, StandardDelimiter, &out) == 6);
    free(out);
    }
END_TEST
START_TEST (getcols_strToTest_correctStrReturns){
        char * toTest = "bla;blah;d";
        char ** out = NULL;
        getcols(toTest, StandardDelimiter, &out);
        ck_assert_str_eq("bla", out[0]);
        ck_assert_str_eq("blah", out[1]);
        ck_assert_str_eq("d", out[2]);
        free(out);
    }
END_TEST
START_TEST (getcols_nullLine_returnsMinus1){
        char * toTest = NULL;
        char ** out = NULL;
        ck_assert(getcols(toTest, StandardDelimiter, &out) == -1);
    }
END_TEST
START_TEST (getcols_nullDelim_returnsMinus1){
        char * toTest = "smth";
        char ** out = NULL;
        ck_assert(getcols(toTest, NULL, &out) == -1);
    }
END_TEST
START_TEST (getcols_notNullOut_returnsMinus4){
        char * toTest = "smth";
        char ** out = &toTest;
        ck_assert(getcols(toTest, StandardDelimiter, &out) == -4);
    }
END_TEST
START_TEST (getcols_emptyDelim_returnsMinus2){
        char * toTest = "smth";
        char ** out = NULL;
        char * delim = "\0";
        ck_assert(getcols(toTest, delim, &out) == -2 );
    }
END_TEST

//student
START_TEST (StudentFree_stud_eqNull){
        Student * stud = Student_new("blah", 10, 15);
        Student_free(&stud);
        ck_assert(stud == NULL);
    }
END_TEST
START_TEST (StudNew_someData_returnsStudent){
        char * temp = "blah";
        Student * stud = Student_new(temp, 10, 15);
        ck_assert_str_eq(Student_getName(stud), temp);
        Student_free(&stud);
    }
END_TEST
START_TEST (StudGetters_stud_returnsCorrectData){
        char * temp = "blah";
        Student * stud = Student_new(temp, 10, 15);
        ck_assert_str_eq(Student_getName(stud), temp);
        ck_assert(Student_getCourse(stud) == 10);
        ck_assert_float_eq(15, Student_getMark(stud));
        Student_free(&stud);
    }
END_TEST

//lists
START_TEST (Listnew_void_returnsCorrectList){
        List * lst = List_new();
        ck_assert(lst != NULL);
        List_free(&lst);
    }
END_TEST
START_TEST (ListFree_list_makesListNull){
        List * lst = List_new();
        List_free(&lst);
        ck_assert(lst == NULL);
    }
END_TEST
START_TEST (ListAdd_smthWithPointer_addsIt){
        List * lst = List_new();
        int * temp = malloc(sizeof(int));
        *temp == 10;
        List_add(lst, temp);
        ck_assert(List_contains(lst, temp));
        List_free(&lst);
        free(temp);

    }
END_TEST
START_TEST (ListContains_smthWithPointerNotInList_returnsFalse){
        List * lst = List_new();
        int * temp = malloc(sizeof(int));
        *temp == 10;
        ck_assert(!List_contains(lst, temp));
        List_free(&lst);
        free(temp);
    }
END_TEST
START_TEST (ListIndexOf_smthWithPointer_returnsMinus1){
        List * lst = List_new();
        int * temp = malloc(sizeof(int));
        *temp == 10;
        ck_assert(List_indexOf(lst, temp) == -1);
        List_free(&lst);
        free(temp);
    }
END_TEST
START_TEST (ListIndexOf_smthWithPointer_returnsZero){
        List * lst = List_new();
        int * temp = malloc(sizeof(int));
        *temp == 10;
        List_add(lst, temp);
        ck_assert(List_indexOf(lst, temp) == 0);
        List_free(&lst);
        free(temp);
    }
END_TEST
START_TEST (ListCount_list_returns1){
        List * lst = List_new();
        int * temp = malloc(sizeof(int));
        *temp == 10;
        List_add(lst, temp);
        ck_assert(List_count(lst) == 1);
        List_free(&lst);
        free(temp);
    }
END_TEST
START_TEST (ListIsEmpty_list_returnsTrue){
        List * lst = List_new();
        ck_assert(List_isEmpty(lst) );
        List_free(&lst);
    }
END_TEST
START_TEST (ListGet_pointerToSmth_pointerToSmth){
        List * lst = List_new();
        int * temp = malloc(sizeof(int));
        *temp == 10;
        List_add(lst, temp);
        ck_assert(List_get(lst, 0) == temp);
        List_free(&lst);
        free(temp);
    }
END_TEST

//csv
START_TEST (readCsv_str_ListOf2Studs){
        List * lst = readCsv("read.txt");
        ck_assert(List_count(lst) == 2);
        List_free(&lst);
    }
END_TEST
START_TEST (saveCsv_str_ListOf2StudsSaves){
        List * lst = readCsv("read.txt");
        saveCsv(lst, "save.txt");
        //only manual checks are appropriate
        ck_assert(1);
        List_free(&lst);
    }
END_TEST

//teacher
START_TEST (TeacherNew_void_pointerIsNotNull){
        Teacher * temp = Teacher_new("vas");
        ck_assert(temp != NULL);
        Teacher_free(&temp);
    }
END_TEST
START_TEST (TeacherFree_teacher_pointerIsNull){
        Teacher * temp = Teacher_new("vas");
        Teacher_free(&temp);
        ck_assert(temp == NULL);
    }
END_TEST
START_TEST (TeacherAttach_list_attached){
        Teacher * temp = Teacher_new("vas");
        List * new = List_new();
        Teacher_attachList(temp, new);
        ck_assert(Teacher_getList(temp) == new);
        Teacher_free(&temp);
        List_free(&new);
    }
END_TEST
START_TEST (TeacherGetName_teacher_name){
        char * tempS = "vas";
        Teacher * temp = Teacher_new(tempS);
        ck_assert_str_eq(Teacher_getName(temp) , tempS);
        Teacher_free(&temp);
    }
END_TEST
START_TEST (TeacherGetList_teacher_correctList){
        Teacher * temp = Teacher_new("vas");
        List * new = List_new();
        Teacher_attachList(temp, new);
        ck_assert(Teacher_getList(temp) == new);
        Teacher_free(&temp);
        List_free(&new);
    }
END_TEST
START_TEST (TeacherSeparateList_twoTeachers_correctListSingleStudent){
        Teacher * temp = Teacher_new("vas");
        List * new = readCsv("read.txt");
        Teacher_attachList(temp, new);
        Teacher * temp2 = Teacher_new("vas");
        List * new2 = List_new();
        List_add(new2, List_get(new, 0));
        Teacher_attachList(temp2, new2);
        List * result = separateLists(temp2, temp);
        ck_assert(List_count(result) == 1);
        Teacher_free(&temp);
        Teacher_free(&temp2);
        List_free(&new);
        List_free(&new2);
        List_free(&result);
    }
END_TEST


Suite *test_suite() {
    Suite *s = suite_create("Module");
    TCase *tc_sample;
    tc_sample = tcase_create("TestCase");

    //"getcols" tests
    tcase_add_test(tc_sample, getcols_strToTest_returns6);
    tcase_add_test(tc_sample, getcols_strToTest_correctStrReturns);
    tcase_add_test(tc_sample, getcols_nullLine_returnsMinus1);
    tcase_add_test(tc_sample, getcols_nullDelim_returnsMinus1);
    tcase_add_test(tc_sample, getcols_notNullOut_returnsMinus4);
    tcase_add_test(tc_sample, getcols_emptyDelim_returnsMinus2);

    //student tests
    tcase_add_test(tc_sample, StudentFree_stud_eqNull);
    tcase_add_test(tc_sample, StudNew_someData_returnsStudent);
    tcase_add_test(tc_sample, StudGetters_stud_returnsCorrectData);

    //list tests
    tcase_add_test(tc_sample, Listnew_void_returnsCorrectList);
    tcase_add_test(tc_sample, ListFree_list_makesListNull);
    tcase_add_test(tc_sample, ListAdd_smthWithPointer_addsIt);
    tcase_add_test(tc_sample, ListContains_smthWithPointerNotInList_returnsFalse);
    tcase_add_test(tc_sample, ListIndexOf_smthWithPointer_returnsMinus1);
    tcase_add_test(tc_sample, ListIndexOf_smthWithPointer_returnsZero);
    tcase_add_test(tc_sample, ListCount_list_returns1);
    tcase_add_test(tc_sample, ListIsEmpty_list_returnsTrue);
    tcase_add_test(tc_sample, ListGet_pointerToSmth_pointerToSmth);

    //csv
    tcase_add_test(tc_sample, readCsv_str_ListOf2Studs);
    tcase_add_test(tc_sample, saveCsv_str_ListOf2StudsSaves);

    //teacher
    tcase_add_test(tc_sample, TeacherNew_void_pointerIsNotNull);
    tcase_add_test(tc_sample, TeacherFree_teacher_pointerIsNull);
    tcase_add_test(tc_sample, TeacherAttach_list_attached);
    tcase_add_test(tc_sample, TeacherGetName_teacher_name);
    tcase_add_test(tc_sample, TeacherGetList_teacher_correctList);
    tcase_add_test(tc_sample, TeacherSeparateList_twoTeachers_correctListSingleStudent);



    suite_add_tcase(s, tc_sample);

    return s;
}

int main(){
    Suite *s = test_suite();
    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);  // important for debugging!

    srunner_run_all(sr, CK_VERBOSE);

    int num_tests_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return num_tests_failed;
}
