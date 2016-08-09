package main

import (
        "fmt"
        "github.com/tealeg/xlsx"
        "html/template"
        "os"
)

type Person struct {
        Name   string
        Age    int
        Emails []string
        Jobs   []*Job
}

type Job struct {
        Employer string
        Role     string
}

func main() {
        job1 := Job{Employer: "Monash", Role: "Honorary"}
        job2 := Job{Employer: "Box Hill", Role: "Head of HE"}

        person := Person{
                Name:   "jan",
                Age:    50,
                Emails: []string{"jan@newmarch.name", "jan.newmarch@gmail.com"},
                Jobs:   []*Job{&job1, &job2},
        }

        t, err := template.ParseFiles("test.tml")
        checkError(err)

        file, err := os.Create("writeAt.cs")

        err = t.Execute(file, person)
        file.Close()
        checkError(err)
}

func checkError(err error) {
        if err != nil {
                fmt.Println("Fatal error ", err.Error())
                os.Exit(1)
        }
}

// ReadXlsx : read xlsx files
func ReadXlsx(path string) {
    xlsFile, err := xlsx.OpenFile(path)
    if err != nil {
        fmt.Println("err load xlsx file ", err.Error())
    }
    
    for _, sheet := range xlsFile.Sheets {
        for _, row := range sheet.Rows {
            for _, cell := range row.Cells {
                if cell.Value == "" {
                    fmt.Printf("null\n")
                } else {
                    fmt.Printf("%s \n", cell.Value)
                }
            }
        }
    }
}
