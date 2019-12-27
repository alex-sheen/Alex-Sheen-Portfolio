//package com.deenamanat.payroll;
/**
 * @author Deen Amanat
*/

public class MusicTools {

	public static void main(String[] args) {
		double [] array = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
		double [] anotherArray = {1.0, 2.0, 3.0, 4.0};
		double [] equalArray = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
		double [] otherArray = {5.0, 4.0, 3.0, 2.0, 1.0};
		double [] singleArray = {1.0};
		System.out.println("Beginning Tests:");
		System.out.println("Testing printArray:");
		System.out.println("Expected Array: 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0");
		printArray(array);
		System.out.println("End of printArray Test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing arrayToString");
		System.out.println("Expected Array: 1.0,2.0,3.0,4.0,5.0,6.0,7.0");
		System.out.println(arrayToString(array));
		System.out.println("End of arrayToString test");
		/////////////////////
		System.out.println(".");
		System.out.println("Testing arraysAreEqual:");
		System.out.println("Expected Return: True");
		if (arraysAreEqual(array, equalArray)) { System.out.println("True"); }
		System.out.println("End of arraysAreEqual Test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing reverseArray");
		System.out.println("Expected Array: 1.0");
		printArray(reverseArray(singleArray));
		System.out.println("End of reverseArray test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing findArrayMax");
		System.out.println("Expected Array: 7.0");
		findArrayMax(array);
		System.out.println("End of findArrayMax test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing findArrayMin");
		System.out.println("Expected Array: 1.0");
		findArrayMin(array);
		System.out.println("End of findArrayMin test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing scaleArray");
		System.out.println("Expected Array: 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0");
		printArray(scaleArray(array, 2.0));
		System.out.println("End of scaleArray test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing weightedAddArray");
		System.out.println("Expected Array: 3.0, 3.0, 3.0, 3.0, 0.5");
		printArray(weightedAddArray(anotherArray, otherArray, 0.5, 0.5));
		System.out.println("End of weightedAddArray test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing copyArray");
		System.out.println("Expected Array: 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0");
		printArray(copyArray(array, 2, 7));
		System.out.println("End of copyArray test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing cutArray");
		System.out.println("Expected Array: 1.0, 2.0, 6.0, 7.0");
		printArray(cutArray(array, 2, 5));
		System.out.println("End of cutArray test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing concatArray");
		System.out.println("Expected Array: 1.0, 2.0, 3.0, 4.0, 5.0 6.0, 7.0, 5.0, 4.0, 3.0, 2.0, 1.0");
		printArray(concatArray(array, otherArray));
		System.out.println("End of concatArray test");
		////////////////////
		System.out.println(".");
		System.out.println("Testing spliceArray");
		System.out.println("Expected Array: 1.0, 2.0, 5.0, 4.0, 3.0 2.0, 1.0, 3.0, 4.0, 5.0, 6.0, 7.0");
		printArray(spliceArray(array, otherArray, 2));
		System.out.println("End of spliceArray test");
	}

	/**
	* <h1>Prints out the contents of an array!</h1>
	* printArray
	* The printArray method prints out an array
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, an array of doubles to be printed out
	*/

	//printArray beginning WORKS
	public static void printArray(double[] theArray) {
		int length = theArray.length;
		for (int i = 0; i < length; i++) {
			System.out.print(theArray[i]); //Runs through the array and prints each argument
			if (i != (length-1)) {
				System.out.print(", ");
			} else {
				System.out.print(" ");
			}
		}
	}
	//printArray ending

	/**
	* <h1>Returns  the contents of an array as a String!</h1>
	* arrayToString
	* arrayToString converts the contents of an array into a String
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, an array of doubles to be turned into a String
	* @return the contents of theArray as a String
	*/

	//arrayToString beginning WORKS
	public static String arrayToString(double[] theArray) {
		int length = theArray.length;
		String returnedString = "";
		for (int i = 0; i < length; i++) {
			returnedString += Double.toString(theArray[i]);
			if (i != (length-1)) { returnedString += ","; }
		}
		return returnedString;
	}
	//arrayToString ending


	/**
	* <h1>Checks if two arrays are equal in length and content!</h1>
	* arraysAreEqual
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the first array to check for equality
	* @param otherArray, the second array to check for equality
	* @return true or false depending on whether they are equal
	*/


	//arraysAreEqual beginning WORKS
	public static boolean arraysAreEqual(double[] theArray, double [] otherArray) {
		int length = theArray.length;
		int otherLength = otherArray.length;
		int counter = 0;
		if (length == otherLength) {
			if (length == 0) {
				return true;
			}
			for (int i = 0; i < length; i++) {
				if (theArray[i] == otherArray[i]){ counter++; }
			}
			if (counter == length) { return true; }
			else { return false; }
		} else {
			return false;
		}
	}
	//arraysAreEqual ending


	/**
	* <h1>Reverses the contents of an array!</h1>
	* reverseArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the  array to be reversed
	* @return a new reversed array
	*/

	//reverseArray beginning WORKS
	public static double[] reverseArray(double[] theArray) {
		int length = theArray.length;
		double[] newArray = new double [length];
		if (length == 0) { return newArray; }
		if (length == 1) { return theArray; }
		double temporary = 0.0;
		for (int i = 0; i < (length/2); i++) {
			temporary = theArray[i];
			newArray[i] = theArray[length-1-i]; //Sets the first half of the array to the equivalent position in the second half
			newArray[length-1-i] = temporary; //Sets the second half of the array to the equivalent position in the first half
		}
		return newArray;
	}
	//reverseArray ending

	/**
	* <h1>Finds the maximum value of an array!</h1>
	* findArrayMax
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the array to be checked
	* @return the maximum value
	*/

	//findArrayMax beginning WORKS
	public static double findArrayMax(double[] theArray) {
		int length = theArray.length;
		double max = Double.NEGATIVE_INFINITY;
		for (int i = 0; i < length; i++) {
			if (max < theArray[i]) { max = theArray[i]; }
		}
		System.out.println(max);
		return max;
	}
	//findArrayMax end

	/**
	* <h1>Finds the minimum value of an array!</h1>
	* findArrayMin
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the array to be checked
	* @return the minimum value
	*/

	//findArrayMin beginning WORKS
	public static double findArrayMin(double[] theArray) {
		int length = theArray.length;
		double min = Double.POSITIVE_INFINITY;
		for (int i = 0; i < length; i++) {
			if (min > theArray[i]) { min = theArray[i]; }
		}
		System.out.println(min);
		return min;
	}
	//findArrayMin ending


	/**
	* <h1>Scales an array by a scalar value!</h1>
	* scaleArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the array to be scaled
	* @param scalar, the double that will scale the values of the first array
	* @return a new array with the scaled values
	*/

	//scaleArrary beginning WORKS
	public static double[] scaleArray(double[] theArray, double scalar) {
		int length = theArray.length;
		double[] newArray = new double [length];
		if (length == 0) { return newArray; }
		for (int i = 0; i < length; i++) {
			double value = theArray[i];
			newArray[i] = value*scalar;
		}
		return newArray;
	}
	//scaleArray ending WORKS

	/**
	* <h1>Scales and adds two arrays together!</h1>
	* weightedAddArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the first array to be weighted and added
	* @param otherArray, the second array to be weighted and added
	* @param firstWeight, the double value to scale the first array
	* @param secondWeight, the double value to scale the second array
	* @return a new array with both the contents of the orignal arrays weighted and added together
	*/

	//weightedAddArray beginning WORKS
	public static double [] weightedAddArray(double [] theArray, double[] otherArray, double firstWeight, double secondWeight) {
		int length = theArray.length;
		int otherLength = otherArray.length;
		int counter = 0;
		double [] newArray;
		if (firstWeight + secondWeight != 1) {
			System.out.println("The two weights must add up to one");
			newArray = new double [0];
			return newArray;
		}
		if (length > otherLength) { //This is the array created that expands otherArray to match the length of theArray with 0s in the back
			counter = 1;
			newArray = new double [length];
			for (int i = 0; i < otherLength; i++) {
				newArray[i] = otherArray[i];
			}
			for (int i = length; i > otherLength; i--) {
				newArray[i-1] = 0;
			}
		} else if (otherLength > length) { //This is the array created that expands theArray to match the length of otherArray with 0s in the back
			counter = 2;
			newArray = new double [otherLength];
			for (int i = 0; i < length; i++) {
				newArray[i] = theArray[i];
			}
			for (int i = otherLength; i > length; i--) {
				newArray[i-1] = 0;
			}
		} else {
			counter = 3;
			newArray = new double [length];
			for (int i = 0; i < otherLength; i++) {
				newArray[i] = otherArray[i];
			}
		}
		int finalLength = newArray.length;
		double [] finalArray = new double [finalLength];
		if (counter == 1) { //Adds theArray and newArray
			for (int i = 0; i < finalLength; i++) {
				finalArray[i] = (theArray[i]*firstWeight)+(newArray[i]*secondWeight);
			}
		} else if (counter == 2) { //Adds theArray and newArray
			for (int i = 0; i < finalLength; i++) {
				finalArray[i] = (otherArray[i]*firstWeight)+(newArray[i]*secondWeight);
			}
		} else if (counter == 3) {
			for (int i = 0; i < finalLength; i++) {
				finalArray[i] = (theArray[i]*firstWeight)+(newArray[i]*secondWeight);
			}
		}
		return finalArray;
	}
	//weightedAddArray ending

	/**
	* <h1>Copies a portion of an array and returns it!</h1>
	* copyArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the original array which the new array will be pulled from
	* @param inclusive, the number that corresponds with a number in theArray. This argument wil be  the first argument in the new array
	* @param exclusive, the number that corresponds with a number in theArray. The argument before this one will be the final argument in the new array.
	* @return a new array that is a smaller portion of the original array
	*/

	//copyArray beginning WORKS
	public static double[] copyArray(double[] theArray, int inclusive, int exclusive) {
		int length = theArray.length;
		double[] newArray;
		int difference = exclusive-inclusive;
		if (inclusive < 0) {
			System.out.println("Inclusive needs to be bigger than zero");
			newArray = new double [0];
			return newArray;
		}
		if (exclusive < 0) {
			System.out.println("Exclusive needs to be bigger than zero");
			newArray = new double [0];
			return newArray;
		}
		if (difference < 0) {
			System.out.println("Inclusive needs to be smaller than exclusive");
			newArray = new double [0];
			return newArray;
		}
		if (exclusive > length) {
			System.out.println("Exclusive needs to be smaller than the length");
			newArray = new double [0];
			return newArray;
		}
		newArray = new double[difference];
		for (int i = inclusive; i < exclusive; i++) {
			newArray[i-inclusive] = theArray[i];
		}
		return newArray;

	}
	//copyArray ending

	/**
	* <h1>Cuts out a portion of the array and returns the altered array!</h1>
	* cutArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the original array to be cut
	* @param inclusive, the number that corresponds with a number in theArray. This argument wil be the first one to be cut out of the orignal array
	* @param exclusive, the number that corresponds with a number in theArray. The argument before this one will be the final argument to be cut out.
	* @return returns a new array with a portion of the original array cut out (like splice in java)
	*/

	//cutArray beginning WORKS
	public static double[] cutArray(double[] theArray, int inclusive, int exclusive) {
		int length = theArray.length;
		double[] newArray;
		int difference = exclusive-inclusive;
		int newLength = length-difference;
		if (difference < 0) {
			newArray = new double[0];
			System.out.println("Inclusive needs to be smaller than exclusive");
			return newArray;
		}
		if (inclusive < 0) {
			System.out.println("Inclusive needs to be bigger than zero");
			newArray = new double [0];
			return newArray;
		}
		if (exclusive < 0) {
			System.out.println("Exclusive needs to be bigger than zero");
			newArray = new double [0];
			return newArray;
		}
		if (exclusive > length) {
			newArray = new double[0];
			System.out.println("Inclusive and exclusive needs to be smaller than the length");
			return newArray;
		}
		newArray = new double[newLength];
		for (int i = 0; i < inclusive; i++) {
			newArray[i] = theArray[i];
		}
		for (int i = exclusive; i < length; i++) {
			newArray[i-difference] = theArray[i];
		}
		return newArray;
	}
	//cutArray ending

	/**
	* <h1>Puts two arrays together!</h1>
	* concatArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the first array
	* @param otherArray, the second array to be appended
	* @return a new array that is the original two arrays put together
	*/

	//concatArray beginning WORKS
	public static double[] concatArray(double[] theArray, double[] otherArray) {
		int length = theArray.length;
		int otherLength = otherArray.length;
		double[] newArray = new double [length + otherLength];
		for (int i = 0; i < length; i++) {
			newArray[i] = theArray[i];
		}
		for (int i = 0; i < otherLength; i++) {
			newArray[length+i] = otherArray[i];
		}
		return newArray;
	}
	//concatArray ending

	/**
	* <h1>Puts an array into the middle of another array!</h1>
	* spliceArray
	* <p>Javadoc!</p>
	*
	* @author  Deen Amanat
	* @param theArray, the fist array
	* @param otherArray, the second array that will but put somewhere into the first array
	* @param indexNumber, the argument at which the second array will be put into the first array
	* @return a new array that has the second array inside of the first array
	*/

	//spliceArray beginning WORKS
	public static double[] spliceArray(double[] theArray, double[] otherArray, int indexNumber) {
		int length = theArray.length;
		int otherLength = otherArray.length;
		if (indexNumber > length) {
			double[] newArray = new double [0];
			System.out.println("Index has to be within the length of the first array argument");
			return newArray;
		}
		double[] newArray = new double [length + otherLength];
		for (int i = 0; i < indexNumber; i++) {
			newArray[i] = theArray[i];
		}
		for (int i = 0; i < otherLength; i++) {
			newArray[indexNumber+i] = otherArray[i];
		}
		for (int i = indexNumber; i < length; i++) {
			newArray[otherLength+i] = theArray[i];
		}
		return newArray;
	}
	//spliceArray ending



}
