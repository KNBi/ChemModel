from ..models import User, Records, SingleRecord
import copy
from datetime import date


def save_to_db(results, username, formula):
    obj, created = User.objects.get_or_create(username=username)

    record, created = Records.objects.get_or_create(date=date.today(), formula=formula, user=obj)
    # record = Records(date=date.today(), formula=formula, user=obj)
    # record.save()
    if created:
        for i in results:
            obj, created = SingleRecord.objects.get_or_create(picture_base64=i, records=record)
            # single_record = SingleRecord(picture_base64=i, records=record)
            # single_record.save()