#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(){
  // there was a leap year in 2016
  // calculate using the 31 Oct 2016 
  int year=2016, month=10, day=31;
  int yearday = day_of_year(year, month, day);
  printf("For date %d.%d.%d the day of year is %d\n", day, month, year, yearday);
  
  // back out the month and day for a particular yearday
  int *pmonth = &month, *pday = &day;
  month_day(year, yearday, pmonth, pday);
  printf("Backed out the day.year as %d.%d for yearday %d on year %d\n", *pday, *pmonth, yearday, year);
  return(0);
}

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// set the day of the year from month and day
int day_of_year(int year, int month, int day){
  int i, leap;
  
  leap = year%4==0 && year%100!=0 || year%400==0;
  for(i=1; i<month; i++)
    day += daytab[leap][i];
  return(day);
}

// set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday){
  int i, leap;
  leap = year%4==0 && year%100!=0 || year%400==0;
  for(i=1; yearday>daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
