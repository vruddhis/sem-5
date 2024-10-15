import javax.swing.*;
import java.awt.*;

class Assignment extends JFrame {
    int[][] buildings = {
        {3, 13, 9},  
        {1, 11, 15}, 
        {12, 7, 16},
        {14, 3, 25},
        {19, 18, 22},
        {2, 6, 7},
        {23, 13, 29},
        {23, 4, 28}   
    };

    int scalingFactor = 5;  
    int coveredLength = 200; 
    int baseHeight = 200;    

    Assignment() {
        setTitle("Skyline");
        setSize(200, 200);  
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        mergeSort(buildings, 0, buildings.length - 1); 
    }

    void mergeSort(int[][] arr, int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);
            merge(arr, left, middle, right);
        }
    }

    void merge(int[][] arr, int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        int[][] leftArray = new int[n1][];
        int[][] rightArray = new int[n2][];

        for (int i = 0; i < n1; i++) {
            leftArray[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArray[j] = arr[middle + 1 + j];
        }

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (leftArray[i][1] >= rightArray[j][1]) { 
                arr[k] = leftArray[i];
                i++;
            } else {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }

    public void paint(Graphics g) {
        super.paint(g);
        
        int[] covered = new int[coveredLength]; 
        
        
        for (int[] building : buildings) {
            int left = building[0] * scalingFactor; 
            int height = building[1] * scalingFactor; 
            int right = building[2] * scalingFactor; 
    
            for (int x = left; x < right && x < coveredLength; x++) {
                if (height > covered[x]) {
                    covered[x] = height; 
                }
            }
        }
        
        for (int x = 1; x < covered.length; x++) {
            if (covered[x] != covered[x - 1]) {
                int x1 = x; 
                int y1 = baseHeight - covered[x - 1];  //BECAUSE WE ARE IN THE FOURTH QUADRANT
                int y2 = baseHeight - covered[x];     
                
                g.drawLine(x1, y1, x1, y2);
            }
            if (covered[x - 1] > 0) {
                int x1 = x - 1;
                int x2 = x;
                int y1 = baseHeight - covered[x - 1]; 
                int y2 = baseHeight - covered[x - 1]; 
                g.drawLine(x1, y1, x2, y2);  
            }
        }
        
        
    }

    public static void main(String[] args) {
        new Assignment();
    }
}
