 

package obj;

public class Student {
    private String id , name, group , email;

    
    Student(){
        name="Student";
        id="000";
        group="K60CC";
        email="uet@vnu.edu.vn"; 
    }
    
    Student(String nid, String n, String em){
        this.name=nid;
        this.id=n;
        this.email=em;
        this.group="K60CC";
    } 
    
    public void deleteStudent(){
        this.name="0";
        this.group="0";
        this.id="0";
        this.email="0";
    }
    Student(Student s){
        this.email=s.email;
        this.group=s.group;
        this.id=s.id;
        this.name=s.name;
    } 
    public void setId(String n){
        this.id=n;
    }
    
    public String getId(){
        return this.id;
    }
    
    public void setName(String nameTemp){
        this.name=nameTemp;
    }
    
    public String getName(){
        return this.name;
    }
    
    public void setGroup(String groupTemp){
        this.group=groupTemp;
    }
    
    public String getGroup(){
        return this.group;
    }
    
    public void setEmail(String emailTemp){
        this.email=emailTemp;
    }
    
    public String getEmail(){
        return this.email;
    }
    
    
    
    
    
    
}
