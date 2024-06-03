#! /bin/sh
echo "1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Modulus\n6.Exit"
while true;
do
   read -p "Enter choice: " choice
   case $choice in
      1)
         echo "Enter two number"
         read num1
	 read num2
         echo "Sum= $((num1+num2))"
         ;;
       2)
         echo "Enter two number"
 	 read num1
	 read num2
         echo "result= $((num1-num2))"
         ;;
       3)
         echo "Enter two number"
         read num1
         read num2
         echo "Result= $((num1*num2))"
         ;;
       4)
            echo "Enter two numbers:"
            read num1
            read num2
            result=$((num1/num2))
            echo "Result of division: $result"
            ;;
       5)
           echo "Enter two numbers:"
            read num1
            read num2
            result=$((num2%num2))
            echo "Result= $result"
            ;;
        6)
           break;
            ;;
   esac
done
