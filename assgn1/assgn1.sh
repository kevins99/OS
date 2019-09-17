
insert()
{
	echo "Enter details of your car:-\c"
	echo "enter model name:-\c"
	read cname
	echo "Licence plate number:-\c"
	read lno
	echo "Enter pincode of registration:-\c"	
	read pcode
	echo $cname"\t\t"$lno"\t\t"$pcode>>car.txt
	echo "\nRecord inserted\c"
	
}

display() 
{
	echo "\nModel_Name\tl_no\tpincode\n"
	cat car.txt
	echo "\n"
}

search()
{
	echo "\nEnter licence plate Number to be searched:"
	read roll
	grep -w $lno car.txt&&echo"record found\n"
}
delete()
{
	echo "\nEnter licence plate number to be deleted:"
	read lno
	grep -v $lno car.txt > temp.txt||echo "record not founds"
	mv temp.txt car.txt
	echo "\ndeleted"
}
modify()
{
	echo "\nEnter licence plate number to be modified:"
	read lno
	grep -v $lno car.txt > temp.txt||echo "record not found"
	mv temp.txt car.txt
	echo "\ndeleted"
	insert
}

sort1()
{
	echo "\nSorting the records\n"
	sort -k1 car.txt > temp.txt
	mv temp.txt car.txt
}



while(true)
	do
		echo "1.Insert Record  \n"
		echo "2.Display Record \n"
		echo "3.Search Record  \n"
		echo "4.Delete Record  \n"
		echo "5.Modify Record  \n"
		echo "6.Exit"
		echo "7.Sort"
		echo "\nEnter your choice:-\c"
		read choice

		case "$choice" in
				1) insert;;
				2) display;;
				3) search;;
				4) delete;;
				5) modify;;
				6) exit;;
				7) sort1;;
				*) echo "\nYou entered wrong choice"
		esac 
	done

