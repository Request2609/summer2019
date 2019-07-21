import java.util.Scanner;

public class eatChocolate {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt();
		int M = scan.nextInt();
		System.out.println(SearchMaxChocolate(M, N));
	}
	
	public static int SumChocolate(int num,int day){
		int sum = 0;

		for(int i = 1;i <= day;i++){
			sum = sum + num;
			num = (int)Math.ceil((double)num/2);
		}
		return sum;
	}
	
	public static int SearchMaxChocolate(int total, int day){
		int first = 1;
		int last = total;
		int sum = 0;
		int mid = (first + last)/2;;
		//出走的天数和实际的天数相等的话，每天吃一个巧克力
		if(day == total)
			return 1;
    
		while(first <= last){
            
			sum = SumChocolate(mid, day);
			if(sum < total){
				first = mid + 1;
			}else if( sum == total){
				return mid;
			}else {
				last = mid - 1;
			}
			mid = (first + last)/2;
		}
		
		return mid;
	}
}
