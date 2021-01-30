from django.db import models
# Create your models here.


class Record(models.Model):
    date = models.DateField()
    formula = models.CharField(max_length=50)
    results = models.TextField()






