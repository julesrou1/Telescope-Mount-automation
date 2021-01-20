public class Data {

    /* sert à stocker les valeurs qu'on va chercher dans la bdd */
    protected String ra;
    protected String dec;

    public Data(){
        ra="0.0";
        dec="0.0";
    }


    public void setRa(String a){ra=a;}

    public void setDec(String b){dec=b;}

    public void printData(){
        System.out.println(this.ra);
        System.out.println(this.dec);
    }

}
