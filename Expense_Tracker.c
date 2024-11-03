#define NAME_LEN 50
#define CATEGORY_LEN 50
#define REC_USER_LEN 100
#define REC_FAM 100
#define EXP_CATEGORY 50
#define DATE 20
#define REC_EXP_LEN 20
#include<stdio.h>
#include<string.h>
int flag_value=1,len_fam_array=0,w=0,num_user_recs=0,num_exp_recs=0;

//w stands for the index of rec_fam array of structures, flag_value id the fam_id given by system






struct user{
    unsigned int user_id;
    char name[NAME_LEN];
    float income;
};
struct user rec_user[REC_USER_LEN];

struct fam{
    int fam_id,fam_mem_id[5]; // this will be referenced from struct user 
    char fam_name[NAME_LEN];
    float fam_income,fam_expense;
    // struct user member; not req ig
};
struct fam rec_fam[REC_FAM];

struct date {
    int date,month;
    //for simplicity , 10days=1month
};

struct expense{
    int expense_id;
    char expense_cat[CATEGORY_LEN];// also check for whether date will be int or string 
    float exp_amt;
    struct user person; // but we will be using only the person.user_id part of it 
    struct date exp_date;
};
struct expense user_expense[REC_USER_LEN];






void initialize_db_user(struct user rec_user[],int size){
    
    for(int i=0;i<size;i++){
        rec_user[i].user_id=0;
        rec_user[i].name[0]='\0';
        rec_user[i].income=0.00;

    }
    printf("User database initialized \n ");
}

void initialize_db_expense(struct expense user_expense[],int size){
    
    for(int i=0;i<size;i++){
        
        user_expense[i].expense_cat[0]='\0';
        user_expense[i].expense_id=0;
        user_expense[i].exp_amt=0.00;
        user_expense[i].exp_date.date=0;
        user_expense[i].exp_date.month=0;
        user_expense[i].person.user_id=0;

    }
    printf("Expense database initialized \n ");

}

void initialize_db_fam(struct fam rec_fam[REC_FAM],int size){
    int i;
    for(int i=0;i<size;i++){
        rec_fam[i].fam_name[0]='\0';
        rec_fam[i].fam_expense=0.00;
        rec_fam[i].fam_income=0.00;
        for(int j=0;j<4;j++){
        rec_fam[i].fam_mem_id[j]=0;
        }
        rec_fam[i].fam_id=0;
    }
    printf("Family database initialized \n");
}

void create_joinFamily(int cj,struct fam rec_fam[],int size,int id);
void addUser( struct user rec_user[],int size){
    

    int j=0,is_free_loc=0,cj,id;
    float money_in;
    struct user temp;
    char std_name[NAME_LEN];
    int flag = 1;
    while(flag==1){
        flag=0;
        printf("Enter user id: \n");
        scanf("%d",&id);
        int i=0,j=num_user_recs-1;
        while((i<=j)&& (!flag)){
            int mid = (i+j)/2;
            if(rec_user[mid].user_id==id){
                flag = 1;
                printf("Id already exists \n");
            }else if(rec_user[mid].user_id < id){
                i = mid+1;
            }else{
                j = mid -1;
            }
        }

    }
    
    printf("Enter name: \n");
    scanf("%s",std_name);

    printf("Enter income: \n");
    scanf("%f",&money_in);
    

    while((j<size)&&(is_free_loc==0)){
        if(rec_user[j].user_id==0){
            is_free_loc=1;
        }
        else{
            j++;
        }
    }
    if(is_free_loc==1){
        strcpy(rec_user[j].name,std_name);
        rec_user[j].income=money_in;
        rec_user[j].user_id=id;

        /*now we want to add this record/user to a sorted array. Therefore will use concept
        of inertion sort*/
        // putting min element at first position
        int x = rec_user[j].user_id;
        struct user temp = rec_user[j];

        // Shift elements to the right and insert the new user in the correct position
        int i = j - 1;
        while (i >= 0 && rec_user[i].user_id > x) {
            rec_user[i + 1] = rec_user[i];  // Shift right
            i--;
        }
        rec_user[i + 1] = temp;  // Insert the new user at the correct position
        num_user_recs += 1;  // Increment the number of user records

        int flag_fam=1;
        while(flag_fam==1){
            printf("Enter 1 if you want to create a family or enter 0 if you want to join a family");
            scanf("%d",&cj);
            // maybe possible that cj needs to be defined globally because it is required in the create_joinFamily function
            if(cj==1){
                create_joinFamily(cj, rec_fam,REC_FAM,id);
                flag_fam=0;
            }
            else if(cj==0){
                create_joinFamily(cj, rec_fam,REC_FAM,id);
                flag_fam=0;
            }
            else{
                printf("Invalid input");
                
            }
        }

    }
    else{
        printf("No free space available to add a new user.\n");
    }
    
    

 
}


void addExpense(struct expense user_expense[],int size,struct user rec_user[],int length){
    int j=0,is_free_loc=0,is_true_user=1,exp_id,id,date,month;
    float money_out;
    char exp_cat[CATEGORY_LEN];
    struct date exp_date;
    

    while(is_true_user==1)
    {
        printf("Enter the user id of the person whose expense record is to be stored: \n");
        scanf("%d",&id);
        //using binary search 
        int ret_val=-1;
        int found=0;
        int i=0;

        while((i<num_user_recs)&&!found){
            if(rec_user[i].user_id==id){
                found=1;
                ret_val=i;
            }
            else{
                i++;
            }
        }

        if(ret_val==-1){
            is_true_user=1;
        } 
        else{
            printf("Give expense id: \n");
            scanf("%d",&exp_id);
            // check if it exists initially or not just like u did it for user id 
            // if same user id provided then again ask for expense id
            printf("Enter expense category: \n");
            scanf("%s",exp_cat);
            printf("Enter expense amount: \n");
            scanf("%f",&money_out);
            printf("Enter date of transaction:(between 1 and 10) \n");
            scanf("%d",&date);
            printf("Enter month(from 1 to 12): \n");
            scanf("%d",&month);

            is_true_user=0;

        }
    }
    
    while((j<size)&&(is_free_loc==0)){
        if((user_expense[j].expense_id==0)&&(user_expense[j].person.user_id==0)){
            is_free_loc=1;
        }
        else{
            j++;
        }
        if(is_free_loc==1){
            strcpy(user_expense[j].expense_cat,exp_cat);
            user_expense[j].expense_id=exp_id;
            user_expense[j].exp_amt=money_out;
            user_expense[j].exp_date.date=date;
            user_expense[j].exp_date.month=month;
            user_expense[j].person.user_id=id;
        }
    }

    num_exp_recs+=1;
    /*Now we will do sorting based on two factors, first on user_id then on expense_id*/
    int x= user_expense[j].person.user_id;
    int y= user_expense[j].expense_id;
    if(j>0){
        struct expense temp = user_expense[j];  
        int i = j - 1;

        
        while (i >= 0 && 
            (user_expense[i].person.user_id > x || 
            (user_expense[i].person.user_id == x && user_expense[i].expense_id > y))) {
            user_expense[i + 1] = user_expense[i];  // Shift element to the right
            i--;
        }

        // Insert the current element at the correct position
        user_expense[i + 1] = temp;
    }
}


void create_joinFamily(int cj,struct fam rec_fam[],int size,int id){
    int family_id,flag_zero=1;
    char std_fam_name[NAME_LEN];
    int k=0; // k is index of fam_mem_id to be filled 

    if(cj==1){
        
        // k=0 wont be a problem for cj=1, but if cj=0 then .fam_mem_id[i++]=id
        
        

        
        printf("Enter name of family: ");
        scanf("%s",std_fam_name);
        strcpy(rec_fam[w].fam_name,std_fam_name);
        rec_fam[w].fam_mem_id[0]=id;
        rec_fam[w].fam_id=flag_value;
        printf("%d",rec_fam[w].fam_id);



        for(int i=0;i<4;i++){ 
            for(int k=0;k<num_user_recs;k++){
                if(rec_fam[w].fam_mem_id[i]==rec_user[k].user_id){
                    rec_fam[w].fam_income=rec_fam[w].fam_income+rec_user[k].income;;
                }
            }
        }
        

        for(int i=0;i<4;i++){
            for(int k=0;k<num_exp_recs;k++){
                if(rec_fam[w].fam_mem_id[i]==user_expense[k].person.user_id){
                    rec_fam[w].fam_expense=rec_fam[w].fam_expense+user_expense[k].exp_amt;
                }
            }
        }
        

        // here we have used linear search but binary search can also be used by taking into consideration that the user_db is sorted based on ids
                 


        len_fam_array+=1;
        k+=1; // this is crct 
        w+=1;
        flag_value+=1;//define this globally 
            
    }
    // a direct else statement will work because we are ensuring that cj is receiving a value of 0 or 1 from the user 
    else{
        // while(flag_zero==1){
        printf("Enter the family_id of the family you want to join: ");
        scanf("%d",&family_id);
        if(family_id<=0){
            flag_zero=1;
        }
        else{
            
            //searching using binary search whether this id exists or not
            int ret_val=-1;
            int found=0;
            int i=0;

            while((i<len_fam_array)&&!found){
                if(rec_fam[i].fam_id==family_id){
                    found=1;
                    ret_val=i;
                }
                else{
                    i++;
                }
            }

            if(found==1){
                
                int k=0;
                while((rec_fam[i].fam_mem_id[k]!=0) && (k<4)){
                    k++;
                }
                if(k==4){
                    printf("there are already 4 members");
                }
                else{
                    rec_fam[i].fam_mem_id[k]=id;
                    for(int l=0;l<4;l++){ 
                        for(int t=0;t<num_user_recs;t++){
                            if(rec_fam[i].fam_mem_id[l]==rec_user[t].user_id){
                                rec_fam[i].fam_income=rec_fam[i].fam_income+rec_user[t].income;
                            }
                        }
                    }

                    for(int l=0;l<4;l++){
                        for(int k=0;k<num_exp_recs;k++){
                            if(rec_fam[i].fam_mem_id[l]==user_expense[k].person.user_id){
                                rec_fam[i].fam_expense=rec_fam[i].fam_expense+user_expense[k].exp_amt;
                            }
                        }
                    }
                    
                }

                
                
            }
            else{
                printf("Given family id dosent exist");
            

            }
            
        }
            
          
        
      
    }

}

void update_individual_fam_details(struct fam rec_fam[],int size,struct user rec_user[],int length){
    int user_id_chng,flag=0,flag2=0,fam_id_chng;
    float upd_income;
    char upd_name[NAME_LEN],fam_upd_name[NAME_LEN];
    printf("Do you want to delete or update records? delete=1, update=0: \n");
    scanf("%d",&flag);
    if(flag==0){
        printf("Which information do you want to change, individual or family? (family -1/individual 0) \n");
        scanf("%d",&flag2);
        if(flag2==0)
        {
            printf("Which user id information do u want to change: \n");
            scanf("%d",&user_id_chng);
            // check if this user id exists or not 
            printf("If name has to be changed give different name, else provide the same name: \n");
            scanf("%s",upd_name);
            printf("If u want to change the income, give new income else give old income: \n");
            scanf("%f",&upd_income);

            int i=0,found=0;
            while((i<num_user_recs)&&!found){
                if(user_id_chng==rec_user[i].user_id){
                    found=1;
                }
                else{
                    i++;
                }
            }
            // realize that struc user rec_user need not be passed as an argument since it is globally defined 
            if(found==1){
                strcpy(rec_user[i].name,upd_name);
                rec_user[i].income=upd_income;
            }
            else{
                printf("Such an id dosent exist\n");
            }

            rec_fam[i].fam_income = 0.00;
            for(int l=0;l<4;l++){ 
                for(int k=0;k<num_user_recs;k++){
                    if(rec_fam[i].fam_mem_id[l]==rec_user[k].user_id){
                        rec_fam[i].fam_income=rec_fam[i].fam_income+rec_user[k].income;
                    }
                }
            }




        }
        else{
            printf("Which family id information do u want to change: \n");
            scanf("%d",&fam_id_chng);
            //check if it exists or not 
            printf("If name has to be changed give different name, else provide the same name: \n");
            scanf("%s",fam_upd_name);

            int i=0,found=0;
            while((i<len_fam_array)&&!found){
                if(fam_id_chng==rec_fam[i].fam_id){
                    found=1;
                }
                else{
                    i++;
                }
            }
            if(found==1){
                strcpy(rec_fam[i].fam_name,fam_upd_name);
            }
            else{
                printf("Such an id dosent exist,hence operation cannot be performed\n");
            }


        }

    }
    //for deletetion
    else
    {
        printf("Which information do you want to delete, individual or family? (family -1/individual 0) \n");
        scanf("%d",&flag2);
        if(flag2==0)
        {
            printf("Which user id information do u want to delete: \n");
            scanf("%d",&user_id_chng);
            // check if this user id exists or not

            int i=0,found=0;
            while((i<num_user_recs)&&!found){
                if(user_id_chng==rec_user[i].user_id){
                    found=1;
                }
                else{
                    i++;
                }
            }
            
            if(found==1){
                rec_user[i].name[0]='\0';
                rec_user[i].income=0.00;
                rec_user[i].user_id=0;
                //ptr is not maintained therefore sab jaga change nahi hoga 
            }
            else{
                printf("Such an id dosent exist \n");
                //ideally while loop to again prompt the user to enter an id , but too many flags , hence not implemented 
            }

            rec_fam[i].fam_income = 0.00;
            for(int l=0;l<4;l++){ 
                for(int k=0;k<num_user_recs;k++){
                    if(rec_fam[i].fam_mem_id[l]==rec_user[k].user_id){
                        rec_fam[i].fam_income=rec_fam[i].fam_income+rec_user[k].income;
                    }
                }
            }    

                      
        }
        else{
            printf("Which family id information do u want to delete: \n");
            scanf("%d",&fam_id_chng);
            //check if it exists or not

            int i=0,found=0;
            while((i<len_fam_array)&&!found){
                if(fam_id_chng==rec_fam[i].fam_id){
                    found=1;
                }
                else{
                    i++;
                }
            }
            if(found==1){
               rec_fam[i].fam_name[0]='\0';
               rec_fam[i].fam_expense=0.00;
               rec_fam[i].fam_income=0.00;
               for(int j=0;j<4;j++){
                rec_fam[i].fam_mem_id[j]=0;
               }
               rec_fam[i].fam_id=0;
            }
            else{
                printf("Such an id dosent exist \n");
            }

            rec_fam[i].fam_expense = 0.00;
            for(int l=0;l<4;l++){
                for(int k=0;k<num_exp_recs;k++){
                    if(rec_fam[i].fam_mem_id[l]==user_expense[k].person.user_id){
                        rec_fam[i].fam_expense=rec_fam[i].fam_expense + user_expense[k].exp_amt;
                    }
                }
            }
            rec_fam[i].fam_income = 0.00;
            for(int l=0;l<4;i++){ 
                for(int k=0;k<num_user_recs;k++){
                    if(rec_fam[i].fam_mem_id[l]==rec_user[k].user_id){
                        rec_fam[i].fam_income=rec_fam[i].fam_income+rec_user[k].income;
                    }
                }
            }



        }


    }
        
}


void update_delete_expense(struct fam rec_fam[],int size,struct expense user_expense[],int length){
    int exp_id_del,flag,exp_id_upd;//these 2 variables can be grouped together too
    int upd_date,upd_month;
    char upd_exp_cat[CATEGORY_LEN];
    float upd_exp_amt;
    

    printf("Do you want to delete or update expense? delete=1, update=0: \n");
    scanf("%d",&flag);
    // kitne records delete karne hai wo bhi likho ya update 
    // then run while loop utne times in main
    if(flag==1){
        printf("Which expense id information do u want to delete: \n");
        scanf("%d",exp_id_del);
        

        int i=0,found=0;
        while((i<num_exp_recs)&&!found){
            if(exp_id_del==user_expense[i].expense_id){
            found=1;
            }
            else{
            i++;
            }
        }
        if(found==1){
            user_expense[i].expense_cat[0]='\0';
            user_expense[i].expense_id=0;
            user_expense[i].exp_amt=0.00;
            user_expense[i].exp_date.date=0;
            user_expense[i].exp_date.month=0;
            user_expense[i].person.user_id=0;
        }
        // updating family records 
        rec_fam[i].fam_expense = 0.00;  // Reset before recalculating
        for(int l=0;l<4;l++){
            for(int k=0;k<num_exp_recs;k++){
                if(rec_fam[i].fam_mem_id[l]==user_expense[k].person.user_id){
                    rec_fam[i].fam_expense=rec_fam[i].fam_expense + user_expense[k].exp_amt;
                }
            }
        }

    }
    else{
        printf("Which expense id information do u want to update: \n");
        scanf("%d",&exp_id_upd);
        printf("If exp cat has to be changed give different,else provide the same one: \n");
        scanf("%s",upd_exp_cat);
        printf("If u want to change the exp amt, give new exp amt else give old income: \n");
        scanf("%f",&upd_exp_amt);
        printf("If date has to be changed give different,else provide the same one: \n");
        scanf("%d",&upd_date);
        printf("If month has to be changed give different,else provide the same one: \n");
        scanf("%d",&upd_month);
        // also check for whether date will be int or string 
        int i=0,found=0;
        while((i<num_exp_recs)&&!found){
            if(exp_id_upd==user_expense[i].expense_id){
                found=1;
            }
            else{
                i++;
            }
        }
        
        if(found==1){
            strcpy(user_expense[i].expense_cat,upd_exp_cat);
            user_expense[i].exp_amt=upd_exp_amt;
            user_expense[i].exp_date.date=upd_date;
            user_expense[i].exp_date.month=upd_month;
        }

        rec_fam[i].fam_expense = 0.00;  // Reset before recalculating
        for(int l=0;l<4;l++){
            for(int k=0;k<num_exp_recs;k++){
                if(rec_fam[i].fam_mem_id[l]==user_expense[k].person.user_id){
                    rec_fam[i].fam_expense=rec_fam[i].fam_expense + user_expense[k].exp_amt;
                }
            }
        }

    }

}

void get_total_expense(struct fam rec_fam[],int size,struct expense user_expense[],int length){
    int get_fam_id;
    printf("Enter family id: \n");
    
    scanf("%d",&get_fam_id);
    printf("Length of family array is %d \n",len_fam_array);
    int i=0,found=0;
    while((i<len_fam_array)&&!found){
        printf("Family id is %d \n",rec_fam[i].fam_id);
        if(get_fam_id==rec_fam[i].fam_id){
            found=1;
        }
        else{
            i++;
        }
    }
    if(found==1){
        if(rec_fam[i].fam_expense>rec_fam[i].fam_income){
            printf("Given family's expense is more than the family income");
        }
        else{
            printf("Given expense is within the family expenses, that is the family expense is less than the the family income by an amount of %f",rec_fam[i].fam_income-rec_fam[i].fam_expense);
        }

    }
    else{
        printf("Family id not found");
    }

    
}

void get_individual_expense(int given_user_id,struct user rec_user[], int size,struct expense user_expense[],int length){
    int is_true_user=1;
    // search whether user_id is valid or not 
    //  if true then , lets say it returns i as the index of the user_exp array where this id is located 
    while(is_true_user==1)
    {
        printf("Checking if given id is true or not");
        //using binary search 
        int ret_val=-1;
        int found=0;
        int i=0;

        while((i<num_exp_recs)&&!found){
            if(user_expense[i].person.user_id==given_user_id){
                found=1;
                ret_val=i;
            }
            else{
                i++;
            }
        }
// printf("ret_val %d i %d",ret_val,i);
        if(ret_val==-1){
            printf("User id invalid.");
            is_true_user=0;
        } 
        else
        {
            struct ind_cat_exp{
                float amount;
                char category[CATEGORY_LEN];
            };
            
            struct ind_cat_exp rec_individual[5];
            const char cats[5][CATEGORY_LEN] = {"RENT","UTILITY","GROCERY","STATIONARY","LEISURE"};
            for(int x=0;x<5;x++){
                rec_individual[x].amount = 0.00;
                strcpy(rec_individual[x].category,cats[x]);
            }
            
            int sort=0;
            float tot_ind_exp=0.00;
            struct ind_cat_exp temp;

            printf("%d \n",user_expense[i].person.user_id);
            printf("%d \n",given_user_id);
            printf("%d \n",i);
            printf("%d \n",num_exp_recs);

            while((user_expense[i].person.user_id==given_user_id)&& (i<num_exp_recs)){

                printf("while ke andar %s %d\n",user_expense[i].expense_cat,user_expense[i].exp_amt);
                if(strcmp(user_expense[i].expense_cat,"RENT")==0){
                    
                    rec_individual[0].amount+=user_expense[i].exp_amt;
                }
                else if(strcmp(user_expense[i].expense_cat,"UTILITY")==0){
                    
                    rec_individual[1].amount+=user_expense[i].exp_amt;
                }
                else if(strcmp(user_expense[i].expense_cat,"GROCERY")==0){
                    
                    rec_individual[2].amount+=user_expense[i].exp_amt;
                }
                else if(strcmp(user_expense[i].expense_cat,"STATIONARY")==0){
                    
                    rec_individual[3].amount+=user_expense[i].exp_amt;
                }
                else{
                    
                    rec_individual[4].amount+=user_expense[i].exp_amt;
                }
                i++;
                
             
            }
             
            

            for(int k=0;k<5;k++){
                tot_ind_exp=tot_ind_exp+rec_individual[k].amount;
            }
            printf("Total expense for user_id %d is %.2f \n",given_user_id,tot_ind_exp);

            // sorting in descending order bubble sort modified 

            for(int k=0;k<4 && sort==0;k++){
                sort=1;
                for(int j=0;j<4-k;j++){
                    if(rec_individual[j].amount<rec_individual[j+1].amount){
                        temp=rec_individual[j];
                        rec_individual[j]=rec_individual[j+1];
                        rec_individual[j+1]=temp;
                        sort=0;
                    }

                    
                }
                
            }

            for(int l=0;l<5;l++){
                printf("Category: %s\n",rec_individual[l].category);
                printf("Expense amount is %f \n",rec_individual[l].amount);
            }


            is_true_user=0;
        }           
            
    }

}    

void get_categorical_expense_fam(char string_cat[],int size /*main mei wo CATEGORY_LEN hoga*/,struct fam rec_fam[],int length, struct expense user_expense[],int measure)
{
    int flag=1,flag2=1,found=0,found2=0,i=0,j=0,get_fam_id;
    
    while((i<num_exp_recs)&&(found==0)){
        if(strcmp(user_expense[i].expense_cat,string_cat)==0){
            found=1;
        }
        else{
            i++;
        }
    }

    if(found==1){
        printf("Enter family id: ");
        scanf("%d",&get_fam_id);
        
        while((j<len_fam_array)&&(found2==0)){
            if(rec_fam[j].fam_id==get_fam_id){
                found2=1;
            }
            else{
                j++;
            }
        }

        if(found2==1)
        {
            int i=0,m=0,sort=0;
            int len_rec_cat_family=0;
            float tot_fam_cat_exp=0.00;

            struct specific_cat_fam_exp{
                int user_ka_id;
                float user_ka_exp;
            };
            struct specific_cat_fam_exp rec_cat_family[4];
            struct specific_cat_fam_exp temp;

            

            for(int i=0;i<4;i++){
                rec_cat_family[i].user_ka_exp=0.00;
                rec_cat_family[i].user_ka_id=0;
            }

            for(int s=0;s<4;s++){
                
                int m = 0;
                int done = 0;
                while( m < num_exp_recs && !done) {
                    if( user_expense[m].person.user_id == rec_fam[i].fam_mem_id[s] ) {
                        done = 1;
                    }
                    else {
                        m++;
                    }
                }
                done = 0;
                rec_cat_family[s].user_ka_id=user_expense[m].person.user_id;
                while( m < num_exp_recs && !done) {
                    if( (user_expense[m].person.user_id == rec_fam[i].fam_mem_id[s]) ) {
                        if( strcmp(user_expense[m].expense_cat,string_cat)==0) {
                            rec_cat_family[s].user_ka_exp+=user_expense[m].exp_amt;
                        }
                        m++;
                    }
                    else {
                        done = 1;
                    }
                }
                
                    
            }
                
        

            for(int k=0;k<4;k++){
                tot_fam_cat_exp=tot_fam_cat_exp+rec_cat_family[k].user_ka_exp;
            }
            printf("Total expense for family with family id %d and in category %s is %f",get_fam_id,string_cat,tot_fam_cat_exp);

            for(int k=0;k<len_rec_cat_family-1 && sort==0;k++){
                sort=1;
                for(int j=0;j<len_rec_cat_family-k-1;j++){
                    if(rec_cat_family[j].user_ka_exp<rec_cat_family[j+1].user_ka_exp){
                        temp=rec_cat_family[j];
                        rec_cat_family[j]=rec_cat_family[j+1];
                        rec_cat_family[j+1]=temp;
                        sort=0;
                    }
                }
                
            }
            

            for(int l=0;l<4;l++){
                printf("User id: %d \n",rec_cat_family[l].user_ka_id);
                printf("Expense amount is %f \n",rec_cat_family[l].user_ka_exp);
            }
            
        }
        else{
            printf("Family id doesent exist");
            
        }
    }

        
    
    else{
        printf("Invalid category");
        flag=0;
    }
    
}


void get_highest_expense_day(struct fam rec_fam[],int length, struct expense user_expense[],int measure){
    int get_fam_id,flag2,i=0,j=0,found=0,found2=0;
    float date_arr[10];

    for(int s=0;s<10;s++){
        date_arr[s]=0.00;
    }
    printf("Enter family id: ");
    scanf("%d",&get_fam_id);
    
    while((i<len_fam_array)&&(found2==0)){
        if(rec_fam[i].fam_id==get_fam_id){
            found2=1;
        }
        else{
            i++;
        }
    }

    if(found2==1){
        for(int k=0;k<4;k++){
            while((j<num_exp_recs)&&(found==0)){
                if(user_expense[j].person.user_id==rec_fam[i].fam_mem_id[k]){
                    found=1;
                }
                else{
                    j++;
                }
            }

            if(found==1){
                while(user_expense[j].person.user_id==rec_fam[i].fam_mem_id[k]){
                    date_arr[user_expense[j].exp_date.date - 1]=date_arr[user_expense[j].exp_date.date - 1] + user_expense[j].exp_amt;
                    j++;
                }
            }
        }

        float max=date_arr[0];
        int loc=-1;
        for(int m=0;m<10;m++){
            if(date_arr[m]>max){
                max=date_arr[m];
                loc=m;
            }
        }

        printf("Date at which maximum family expense incurred is %d",loc+1);
        printf("Expense amount is %f",max);

        flag2=0;
    }
    else{
        printf("Invlaid family id");
        flag2=0;
    }

    
}

int main(void){
    // struct user user_db[REC_USER_LEN];
    // struct expense expense_db[REC_USER_LEN];
    // struct fam fam_db[100];
    int upd_del_num;

    

    //intitializing the database
    initialize_db_user(rec_user,REC_USER_LEN);
    initialize_db_expense(user_expense,REC_EXP_LEN);
    initialize_db_fam(rec_fam,REC_FAM);

    

    int i=0,k=0,m=0;
    while( i <3){
        addUser(rec_user,REC_USER_LEN);
        i++;
    }
    while(k<5){
        addExpense(user_expense,REC_EXP_LEN,rec_user,REC_USER_LEN);
        k++;
    }
    
    

    update_individual_fam_details(rec_fam,REC_FAM,rec_user,REC_USER_LEN);

    printf("How many expense records do you want to update or delete? \n");
    scanf("%d",&upd_del_num);
    while(m<upd_del_num){
        update_delete_expense(rec_fam,REC_FAM,user_expense,REC_EXP_LEN);
        m++;
    }


    get_total_expense(rec_fam,REC_FAM,user_expense,REC_EXP_LEN);

    

    get_individual_expense(1,rec_user,REC_USER_LEN,user_expense,REC_EXP_LEN);

    get_categorical_expense_fam("RENT",CATEGORY_LEN,rec_fam,REC_FAM, user_expense,REC_USER_LEN);

    get_highest_expense_day(rec_fam,REC_FAM, user_expense,REC_EXP_LEN);



    return 0;
}





    








    