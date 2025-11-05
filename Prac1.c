#!/bin/bash

opt=0
fileName="addressbook.txt" # Default file name

while true
do
    echo -e "\n========= ADDRESS BOOK MENU ========="
    echo "1. Create a New Address Book"
    echo "2. View Records"
    echo "3. Insert New Record"
    echo "4. Delete a Record"
    echo "5. Modify a Record"
    echo "6. Exit"
    echo "====================================="
    echo -n "Enter your choice (1-6): "
    read opt

    case $opt in
    1)
        echo -n "Enter filename for the new address book: "
        read fileName

        if [ -e "$fileName" ]; then
            echo "File '$fileName' already exists. Recreating..."
            rm "$fileName"
        fi

        echo -e "NAME\tNUMBER\t\tADDRESS" > "$fileName"
        echo "======================================" >> "$fileName"

        while true
        do
            echo -n "Enter Name: "
            read name
            echo -n "Enter Phone Number of $name: "
            read number
            echo -n "Enter Address of $name: "
            read address

            echo -e "$name\t$number\t\t$address" >> "$fileName"

            echo -n "Enter 0 to stop, 1 to add another record: "
            read cont
            [ "$cont" -eq 0 ] && break
        done

        echo "Address book '$fileName' created successfully!"
        ;;
    
    2)
        if [ -e "$fileName" ]; then
            echo -e "\n===== Address Book: $fileName ====="
            cat "$fileName"
        else
            echo "File not found! Please create an address book first."
        fi
        ;;

    3)
        if [ ! -e "$fileName" ]; then
            echo "File not found! Please create an address book first."
        else
            echo -n "Enter Name: "
            read name
            echo -n "Enter Phone Number of $name: "
            read number
            echo -n "Enter Address of $name: "
            read address
            echo -e "$name\t$number\t\t$address" >> "$fileName"
            echo "Record inserted successfully!"
        fi
        ;;

    4)
        if [ ! -e "$fileName" ]; then
            echo "File not found! Please create an address book first."
        else
            echo -n "Delete record — Enter Name or Phone Number: "
            read pattern

            if grep -q "$pattern" "$fileName"; then
                grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
                echo "Record(s) matching '$pattern' deleted."
            else
                echo "No matching record found."
            fi
        fi
        ;;

    5)
        if [ ! -e "$fileName" ]; then
            echo "File not found! Please create an address book first."
        else
            echo -n "Modify record — Enter Name or Phone Number: "
            read pattern

            if grep -q "$pattern" "$fileName"; then
                grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"

                echo -n "Enter New Name: "
                read name
                echo -n "Enter Phone Number of $name: "
                read number
                echo -n "Enter Address of $name: "
                read address

                echo -e "$name\t$number\t\t$address" >> "$fileName"
                echo "Record modified successfully!"
            else
                echo "No matching record found to modify."
            fi
        fi
        ;;

    6)
        echo "Exiting program..."
        exit 0
        ;;
    
    *)
        echo "Invalid option! Please try again."
        ;;
    esac
done
