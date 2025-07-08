//递归写法
double findkthnumber(int* nums1,int len1,int* nums2,int len2,int k){

    if(len1>len2){ //保证len1<=len2
        return findkthnumber(nums2,len2,nums1,len1,k);
    }
    if(len1==0){ //len1==0要写在k==1前面，否则可能越界
        return nums2[k-1];
    }
    if(k==1){
        return nums1[0]<nums2[0]?nums1[0]:nums2[0];
    }
    
    int i=(k/2>len1)?len1:k/2;
    int j=k-i;

    if(nums1[i-1]<=nums2[j-1]){
        return findkthnumber(nums1+i,len1-i,nums2,len2,k-i);
    }
    else{
        return findkthnumber(nums1,len1,nums2+j,len2-j,k-j);
    }

}
//迭代做法
double findkthnumber_iter(int* nums1,int len1,int* nums2,int len2,int k){
    int index1=0,index2=0; //关键，记录当前二分位置

    while(1){

        if(len1==index1){
            return nums2[index2+k-1];
        }
        else if(len2==index2){
            return nums1[index1+k-1];
        }
        if(k==1){
            return nums1[index1]<nums2[index2]?nums1[index1]:nums2[index2];
        }

        int half=k/2;

        int newindex1=(index1+half<=len1)?(index1+half):len1;
        int newindex2=(index2+half<=len2)?(index2+half):len2;

        int paviot1=nums1[newindex1-1];
        int paviot2=nums2[newindex2-1];
        
        if(paviot1<=paviot2){
            k-=(newindex1-index1);
            index1=newindex1;
        }
        else{
            k-=(newindex2-index2);
            index2=newindex2;
        }
    }
}
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int total=nums1Size+nums2Size;
    if(total%2==0){
        int left=findkthnumber(nums1,nums1Size,nums2,nums2Size,total/2);
        int right=findkthnumber(nums1,nums1Size,nums2,nums2Size,total/2+1);
        return (left+right)/2.0; //小数除法
    }
    else{
        return findkthnumber(nums1,nums1Size,nums2,nums2Size,total/2+1);
    }
}