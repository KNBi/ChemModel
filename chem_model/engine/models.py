from django.db import models
# Create your models here.


class User(models.Model):
    username = models.CharField(max_length=150, primary_key=True)


class Records(models.Model):
    date = models.DateField()
    formula = models.CharField(max_length=50)
    user = models.ForeignKey(User, on_delete=models.CASCADE)


class SingleRecord(models.Model):
    picture_base64 = models.CharField(max_length=9000000)
    records = models.ForeignKey(Records, on_delete=models.CASCADE)





