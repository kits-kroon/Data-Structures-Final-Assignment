// REGIST.CPP - Student class implementation.

#include "student.h"
#include <algorithm>

Student::Student()
{
  SetStudentId(0);
  SetFirstName("NOT INIT");
  SetLastName("NOT INIT");
  results = new MyVector<Results>();
}

Student::Student(const Student &obj)
{
    results = new MyVector<Results>();
    Copy(obj);
}

Student::~Student()
{
    Clear();
}

        //-------------------- GETTERS --------------------//

const string Student::GetFirstName() const
{
    return fName;
}

const string Student::GetLastName() const
{
    return lName;
}

const unsigned Student::GetSize() const
{
  return results -> GetSize();
}

const long Student::GetStudentId() const
{
    return studentId;
}

const string Student::GetUnitId(unsigned i) const
{
    return (*results)[i].GetUnitId();
}

const unsigned Student::GetDay(unsigned i) const
{
    return (*results)[i].GetDay();
}

const unsigned Student::GetMonth(unsigned i) const
{
    return (*results)[i].GetMonth();
}

const unsigned Student::GetYear(unsigned i) const
{
    return (*results)[i].GetYear();
}

const double Student::GetResult(unsigned i) const
{
    return (*results)[i].GetResult();
}

const unsigned Student::GetResultSemester(unsigned i) const
{
    return (*results)[i].GetSemester();
}

const unsigned Student::GetResultsSize() const
{
    return results -> GetSize();
}

const string Student::GetDate(unsigned i) const
{
    return (*results)[i].GetDate();
}
    //------------------------- SETTERS ---------------------//

void Student::SetStudentId(long sId)
{
    studentId = sId;
}

void Student::SetFirstName(string first)
{
    fName = first;
}

void Student::SetLastName(string last)
{
    lName = last;
}

void Student::SetUnitId(unsigned i, string id)
{
    (*results)[i].SetUnitId(id);
}

void Student::SetResult(unsigned i, double res)
{
    (*results)[i].SetResult(res);
}

void Student::SetResultSemester(unsigned i, unsigned sem)
{
    (*results)[i].SetSemester(sem);
}

void Student::SetDay(unsigned i, unsigned day)
{
    (*results)[i].SetDay(day);
}

void Student::SetMonth(unsigned i, unsigned month)
{
    (*results)[i].SetMonth(month);
}

void Student::SetYear(unsigned i, unsigned year)
{
    (*results)[i].SetYear(year);
}

    //--------------------- CALCULATIONS ---------------//

const double Student::CalculateGPA(BinaryTree<Unit> & units)
{
    /*
     * Information on calculating a GPA according to this format can
     * be found at https://www.murdoch.edu.au/students/myinfo/GPA.html
     * this information was created by Murdoch University and is not
     * my own work.
     *
     */
    double totalCreditPoints; // Total Credit points
    double preDivisionTotal;  // Achievable Credit Points * GPA Value
    double GPA;               // The final GPA value

    preDivisionTotal = 0;   // Initialized to zero
    totalCreditPoints = 0;  // Initialized to zero
    GPA = 0;

    for(unsigned i = 0; i < GetSize(); i++)
    {
        UnitGPACalc(units, totalCreditPoints, preDivisionTotal, i);
    }

    GPA = preDivisionTotal / totalCreditPoints;

    return GPA;
}

const double Student::CalculateGPA(BinaryTree<Unit> & units, unsigned year)
{
    double totalCreditPoints;
    double preDivisionTotal;
    double GPA;

    preDivisionTotal = 0;
    totalCreditPoints = 0;
    GPA = 0;

    for(unsigned i = 0; i < GetSize(); i++)
    {
        if(year == atoll(GetUnitId(i).substr(3, 1).c_str()))
        {
             UnitGPACalc(units, totalCreditPoints, preDivisionTotal, i);
        }
    }
    if(preDivisionTotal == 0 && totalCreditPoints == 0)
        return 0;
    else
        GPA = preDivisionTotal / totalCreditPoints;

    return GPA;
}

const void Student::UnitGPACalc(BinaryTree<Unit> & units, double & tcp, double & pdt, unsigned i)
{
    SetUnit(GetUnitId(i), units); // Sets static unit statUnit

    if(GetResult(i) >= 80) // HD
    {
        pdt += statUnit.GetCredits() * 4;
    }
    else if(GetResult(i) >= 70) // D
    {
        pdt += statUnit.GetCredits() * 3;
    }
    else if(GetResult(i) >= 60) // C
    {
        pdt += statUnit.GetCredits() * 2;
    }
    else if(GetResult(i) >= 50) // P
    {
        pdt += statUnit.GetCredits() * 1;
    }

    tcp += statUnit.GetCredits(); // Counts the total credits including fails
}

const unsigned Student::GetHighestMark() const
{
    unsigned highest = 0; // Initializes to lowest possible mark

    for(unsigned i = 0; i < GetSize(); i++)
    {
        if(highest < GetResult(i))
        {
            highest = GetResult(i);
        }
    }

    return highest;
}

const unsigned Student::GetLowestMark() const
{
    unsigned lowest = 101; // Above highest as it will never be reached

    for(unsigned i = 0; i < GetSize(); i++)
    {
        if(lowest > GetResult(i))
        {
            lowest = GetResult(i);
        }
    }

    return lowest;
}

    //--------------------- OTHERS ---------------------//

void Student::Clear()
{
  if(results != NULL)
  {
      delete results;
  }

  results = NULL;
}

void Student::Copy(const Student &obj)
{
    if(this != &obj)
    {
        delete results;
        results = new MyVector<Results>();

        SetStudentId(obj.GetStudentId());
        SetFirstName(obj.GetFirstName());
        SetLastName(obj.GetLastName());

        for(unsigned i = 0; i < obj.GetSize(); i++)
        {
            SetUnitId(i, obj.GetUnitId(i));
            SetResult(i, obj.GetResult(i));
            SetResultSemester(i, obj.GetResultSemester(i));
            SetDay(i, obj.GetDay(i));
            SetMonth(i, obj.GetMonth(i));
            SetYear(i, obj.GetYear(i));
        }

    }
}

void Student::SetUnit(const Unit &newUnit)
{
    statUnit.SetName(newUnit.GetName());
    statUnit.SetId(newUnit.GetId());
    statUnit.SetCredits(newUnit.GetCredits());
}

const bool Student::SetUnit(string unitId, BinaryTree<Unit> & units)
{
    Unit searchUnit;
    searchUnit.SetId(unitId);

    static void (*sU)(const Unit&);
    sU = &SetUnit;

    if(units.Search(searchUnit, sU))
    {
        return true;
    }

    statUnit.SetName("NotFound");
    statUnit.SetId("NotFound");
    statUnit.SetCredits(0);

    return false;
}

const string Student::GetUnitName()
{
    return statUnit.GetName();
}

Unit Student::statUnit;
